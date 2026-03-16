

#include "y/config/platform.h"
#include "y/memory/zombie.hpp"
#include "y/system/exception.hpp"
#include "y/ability/latch.hpp"

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


        class Nucleus :: Code
        {
        public:
            inline Code() :
#if defined(Y_BSD)
            attr(),
            mutex(attr)
#endif
#if defined(Y_WIN)
            mutex()
#endif
            {

            }

            inline ~Code() noexcept {}


#if defined(Y_BSD)
            SystemMutex::Attribute attr;
#endif
            SystemMutex            mutex;
            static uint64_t        RAM;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        uint64_t         Nucleus::Code::RAM = 0;
        const uint64_t & Nucleus::RAM       = Nucleus::Code::RAM;
        
        namespace
        {
            static void    * NucleusWorkspace[ Alignment::WordsFor<Nucleus::Code>::Count ];
            static Nucleus * NucleusInstance = 0;
        }



        void Nucleus:: deleteCode() noexcept
        {
            assert(0!=code);
            Destruct(code);
            Coerce(code) = 0;
            Y_BZero(NucleusWorkspace);
        }

        Nucleus:: Nucleus() : code( new ( Y_BZero(NucleusWorkspace) ) Code()  )
        {
            assert(0==NucleusInstance);
            try
            {
                System::AtExit::Perform(SelfDestruct,this,LifeTime);
            }
            catch(...)
            {
                deleteCode();
                throw;
            }
            NucleusInstance = this;
            if(Verbose) Display("+", CallSign, LifeTime);

        }

        Nucleus:: ~Nucleus() noexcept
        {
            assert(0!=NucleusInstance);
            if(Verbose) Display("~", CallSign, LifeTime);
            if(RAM>0) {
                std::cerr << "*** Still Active RAM  = " << RAM << std::endl;
            }
            deleteCode();
            NucleusInstance = 0;
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

        Lockable & Nucleus:: giant() noexcept
        {
            assert(code);
            return code->mutex;
        }

    }

    Lockable & Lockable:: Giant()
    {
        static Lockable & _ = Concurrent::Nucleus::Instance().giant();
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



            // allocating
            Y_Lock(code->mutex);
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

            const size_t blockSize = size_t(1) << shift; assert(Code::RAM>=blockSize);
            Code::RAM -= blockSize;
            free(page);
        }


    }

}

