#include "y/config/platform.h"
#include "y/memory/type/single.hpp"
#include "y/system/exception.hpp"
#include "y/ability/latch.hpp"
#include "y/memory/book.hpp"
#include "y/memory/small/house.hpp"
#include "y/memory/small/blocks.hpp"

#include "y/concurrent/thread.hpp"

#if defined(Y_BSD)
#include "sys/bsd.hxx"
#endif // defined(Y_BSD)

#if defined(Y_WIN)
#include "sys/win.hxx"
#endif // defined(Y_WIN)


#include "y/concurrent/nucleus.hpp"
#include "y/type/destruct.hpp"
#include "y/core/meta-max.hpp"

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
            static const size_t MutexSize  = sizeof(SystemMutex);
            static const size_t CondSize   = sizeof(SystemCondition);
            static const size_t ThreadSize = sizeof(SystemThread);
            static const size_t CommSize   = MetaMaxOfTriplet<MutexSize,CondSize,ThreadSize>::Value;

            explicit Data(Memory::Book &book,
                          Lockable     &lock) :
            blocks(book,lock),
            arena( CommSize, book, lock),
            mutexes(arena),
            conditions(arena),
            threads(arena)
            {
            }

            virtual ~Data() noexcept
            {
            }

            Memory::Small::Blocks                  blocks;
            Memory::Small::Arena                   arena;
            Memory::Small::House<SystemMutex>      mutexes;
            Memory::Small::House<SystemCondition>  conditions;
            Memory::Small::House<SystemThread>     threads;

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
            std::cerr << "sizeof(SystemThread)    = " << sizeof(SystemThread)    << std::endl;
            std::cerr << "CommSize                = " << Data::CommSize          << std::endl;

#if defined(Y_BSD)
            std::cerr << "sizeof(pthread_mutex_t) = " << sizeof(pthread_mutex_t) << std::endl;
            std::cerr << "sizeof(pthread_cond_t)  = " << sizeof(pthread_cond_t)  << std::endl;
            std::cerr << "sizeof(pthread_t)       = " << sizeof(pthread_t)       << std::endl;
#endif
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

#include "nucleus/allocator.hxx"



#include "nucleus/factory.hxx"
#include "nucleus/mutex.hxx"
#include "nucleus/thread.hxx"


