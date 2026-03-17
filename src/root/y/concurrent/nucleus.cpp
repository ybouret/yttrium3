#include "y/config/platform.h"
#include "y/memory/type/zombie.hpp"
#include "y/system/exception.hpp"
#include "y/ability/latch.hpp"
#include "y/memory/book.hpp"
#include "y/memory/small/house.hpp"

#if defined(Y_BSD)
#include "sys/bsd.hxx"
#endif // defined(Y_BSD)

#if defined(Y_WIN)
#include "sys/win.hxx"
#endif // defined(Y_WIN)


#include "y/concurrent/nucleus.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/destruct.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const        Nucleus:: CallSign = "Concurrent::Nucleus";
        const char *              Nucleus:: callSign() const noexcept { return CallSign; }
        System::AtExit::Longevity Nucleus:: lifeTime() const noexcept { return LifeTime; }


        //______________________________________________________________________
        //
        //
        //
        //! Implementation of Nucleus with LEVEL-1 cache
        //
        //
        //______________________________________________________________________
        class Nucleus :: Code
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! create the core mutex and core memory handling
            inline Code(Memory::PageFactory &factory) :
#if defined(Y_BSD)
            attr(),
            mutex(attr),
#endif
#if defined(Y_WIN)
            mutex(),
#endif
            book(factory,mutex)
            {

            }

            // cleanup
            inline ~Code() noexcept {}

            //__________________________________________________________________
            //
            //
            // Member
            //
            //__________________________________________________________________

#if defined(Y_BSD)
            SystemMutex::Attribute attr;       // for recursive mutex
#endif
            SystemMutex                         mutex;      // system mutex wrapper
            Memory::Book                        book;       // global pages


            //__________________________________________________________________
            //
            //
            // Data
            //
            //__________________________________________________________________
            static uint64_t        RAM;        // memory monitoring

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        uint64_t         Nucleus::Code::RAM = 0;
        const uint64_t & Nucleus::RAM       = Nucleus::Code::RAM;


        //! contains LEVEL-2 caches
        class Nucleus :: Data
        {
        public:
            explicit Data(Memory::Book &book,
                          Lockable     &lock) :
            mutexArena( sizeof(SystemMutex), book, lock),
            mutexes(mutexArena)
            {
                std::cerr << "---- Creating Data" << std::endl;
            }

            virtual ~Data() noexcept
            {
                std::cerr << "---- Deleting Data" << std::endl;

            }

            Memory::Small::Arena               mutexArena;
            Memory::Small::House<SystemMutex>  mutexes;

        private:
            Y_Disable_Copy_And_Assign(Data);
        };

        namespace
        {
            static void    * NucleusCode[ Alignment::WordsFor<Nucleus::Code>::Count ];
            static void    * NucleusData[ Alignment::WordsFor<Nucleus::Data>::Count ];
            static Nucleus * NucleusInstance = 0;
        }




        void Nucleus:: destructCode() noexcept
        {
            assert(0!=code);
            if(data)
            {
                Destruct(data);
                Coerce(data) = 0;
                Y_BZero(NucleusData);
            }
            Destruct(code);
            Coerce(code) = 0;
            Y_BZero(NucleusCode);

        }

        Memory::PageFactory & Nucleus:: factory() noexcept
        {
            return *this;
        }

        Nucleus:: Nucleus() :
        Singulet(),
        Memory::Allocator(),
        Memory::PageFactory(),
        code( new ( Y_BZero(NucleusCode) ) Code( factory() )  ),
        data( 0 ),
        access(code->mutex),
        book(code->book)
        {
            assert(0==NucleusInstance);
            try
            {
                System::AtExit::Perform(SelfDestruct,this,LifeTime);
                Coerce(data) = new ( Y_BZero(NucleusData) ) Data(book,access);
            }
            catch(...)
            {
                destructCode();
                throw;
            }
            NucleusInstance = this;
            if(Verbose) Display("+", CallSign, LifeTime);
            std::cerr << "sizeof(Code) = " << sizeof(Code) << std::endl;
            std::cerr << "sizeof(Data) = " << sizeof(Data) << std::endl;
            std::cerr << "sizeof(SystemMutex)     = " << sizeof(SystemMutex)     << std::endl;
            std::cerr << "sizeof(SystemCondition) = " << sizeof(SystemCondition) << std::endl;

        }

        Nucleus:: ~Nucleus() noexcept
        {
            assert(0!=NucleusInstance);
            if(Verbose) Display("~", CallSign, LifeTime);
            destructCode();
            NucleusInstance = 0;
            if(RAM>0) {
                std::cerr << "*** Still Active RAM  = " << RAM << std::endl;
            }
        }

        void Nucleus:: SelfDestruct(void *const args) noexcept
        {
            assert(0!=args);
            static_cast<Nucleus *>(args)->~Nucleus();
        }


        Nucleus & Nucleus:: Instance()
        {
            static void *    workspace[ Alignment::WordsFor<Nucleus>::Count ];
            static Nucleus & nucleus = * new ( Y_BZero(workspace) ) Nucleus();

            assert(0!=NucleusInstance);
            return nucleus;
        }

        Nucleus & Nucleus:: Location() noexcept
        {
            assert(0!=NucleusInstance);
            return *NucleusInstance;
        }


    }

    Lockable & Lockable:: Giant()
    {
        static Lockable & _ = Concurrent::Nucleus::Instance().access;
        return _;
    }

}

#include "y/format/decimal.hpp"
#include "y/libc/block/zeroed.h"
#include <cerrno>

namespace Yttrium
{
    namespace Concurrent
    {

        void * Nucleus:: acquire(size_t & blockSize)
        {
            Y_Lock(code->mutex);
            if(blockSize>0)
            {
                void * const blockAddr = calloc(1,blockSize);
                if(!blockAddr)
                {
                    const Decimal fmt(blockSize);
                    blockSize = 0;
                    throw Libc::Exception(ENOMEM,"Acquire(%s)",fmt.c_str());
                }
                assert(Yttrium_Zeroed(blockAddr,blockSize));
                Code::RAM += blockSize;
                return blockAddr;
            }
            else
            {
                return 0;
            }
        }

        void Nucleus:: release(void * &blockAddr, size_t &blockSize) noexcept
        {
            if(blockAddr)
            {
                Y_Lock(code->mutex);
                free(blockAddr);
                Code::RAM -= blockSize;
                blockSize = 0;
                blockAddr = 0;
            }
            else
            {
                assert(0==blockSize);
            }
        }

    }

}

namespace Yttrium
{
    namespace Concurrent
    {
        SystemMutex * Nucleus:: acquireSystemMutex()
        {
            Y_Lock(access);
            assert(data);
            assert(code);
#if defined(Y_BSD)
            return data->mutexes.produce(code->attr);
#endif

#if defined(Y_WIN)
            return data->mutexes.produce();
#endif
        }

        void Nucleus:: releaseSystemMutex(SystemMutex * const mutex) noexcept
        {
            Y_Lock(access);
            assert(mutex);
            assert(data);
            data->mutexes.recycle(mutex);
        }


    }

}

#include "y/memory/metrics.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        

        Memory::Page * Nucleus:: acquirePage(const unsigned shift)
        {
            static const char fn[] = "Nucleus::acquirePage";
            assert(shift>=Memory::Metrics::MinPageShift);
            assert(shift<=Memory::Metrics::MaxPageShift);
            assert(code);
            
            // allocating
            Y_Lock(access);
            const size_t blockSize = size_t(1) << shift;
            void * const blockAddr = calloc(1,blockSize);
            if(!blockAddr)
                throw Libc::Exception(ENOMEM,"%s(2^%u)",fn,shift);

            // updating
            Code::RAM += blockSize;
            Memory::Page * const page = static_cast<Memory::Page *>(blockAddr);
            assert(0==page->next);
            assert(0==page->prev);
            return page;
        }


        void Nucleus:: releasePage(Memory::Page *const page, const unsigned int shift) noexcept
        {
            assert(0!=page);
            assert(shift>=Memory::Metrics::MinPageShift);
            assert(shift<=Memory::Metrics::MaxPageShift);

            Y_Lock(access);
            const size_t blockSize = size_t(1) << shift; assert(Code::RAM>=blockSize);
            Code::RAM -= blockSize;
            free(page);
        }


    }

}

#include "y/concurrent/mutex.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        static SystemMutex * AcquireSystemMutex()
        {
            static Nucleus &nucleus = Nucleus::Instance();
            return nucleus.acquireSystemMutex();
        }



        Mutex:: Mutex() : handle( AcquireSystemMutex() )
        {
        }

        Mutex:: ~Mutex() noexcept
        {
            static Nucleus &nucleus = Nucleus::Location();
            nucleus.releaseSystemMutex(handle);
            Coerce(handle) = 0;
        }

        void Mutex:: lock() noexcept
        {
            assert(handle);
            handle->lock();
        }

        void Mutex:: unlock() noexcept
        {
            assert(handle);
            handle->unlock();
        }

        bool Mutex:: tryLock() noexcept
        {
            assert(handle);
            return handle->tryLock();
        }

    }
}
