

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
#include <cerrno>

namespace Yttrium
{
    namespace Concurrent
    {
        void * Nucleus:: Acquire(size_t & blockSize)
        {
            static Lockable &_ = Instance().giant();
            Y_Lock(_);
            
            if(blockSize>0)
            {
                void * const blockAddr = calloc(1,blockSize);
                if(!blockAddr)
                {
                    const Decimal fmt(blockSize);
                    blockSize = 0;
                    throw Libc::Exception(ENOMEM,"Acquire(%s)",fmt.c_str());
                }
                Code::RAM += blockSize;
                return blockAddr;
            }
            else
            {
                return 0;
            }
        }

        void Nucleus:: Release(void *&blockAddr, size_t &blockSize) noexcept
        {
            if(0!=blockAddr)
            {
                // sanity check
                assert(blockSize>0);
                assert(0!=NucleusInstance);
                assert(blockSize<=RAM);

                // get lock
                static Lockable &_ = NucleusInstance->code->mutex;
                Y_Lock(_);

                // free memory
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

