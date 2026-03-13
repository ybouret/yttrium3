

#include "y/config/platform.h"
#include "y/memory/zombie.hpp"
#include "y/system/exception.hpp"
#include "y/ability/latch.hpp"

#if defined(Y_BSD)
#include <pthread.h>

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! pthread mutex wrapper
        //
        //
        //______________________________________________________________________
        class SystemMutex : public Latch
        {
        public:
            //__________________________________________________________________
            //
            //
            //! mutex attribute so set recursive
            //
            //__________________________________________________________________
            class Attribute
            {
            public:
                inline explicit Attribute() : attr() { init(); settype(); }
                inline virtual ~Attribute() noexcept { destroy(); }

                pthread_mutexattr_t * operator*() noexcept { return attr(); }

            private:
                Y_Disable_Copy_And_Assign(Attribute);
                Memory::Zombie<pthread_mutexattr_t> attr;

                inline void init() {
                    const int err = pthread_mutexattr_init( attr() );
                    if(0!=err) throw Libc::Exception(err,"pthread_mutexattr_init");
                }

                inline void settype() {
                    const int err = pthread_mutexattr_settype( attr(), PTHREAD_MUTEX_RECURSIVE);
                    if(0!=err) {
                        destroy();
                        throw Libc::Exception(err,"pthread_mutexattr_settype(RECURSIVE)");
                    }
                }

                inline void destroy() noexcept { (void) pthread_mutexattr_destroy( attr() ); }
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit SystemMutex(Attribute &attr) : mutex()
            {
                const int err = pthread_mutex_init( mutex(), *attr );
                if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
            }

            inline virtual ~SystemMutex() noexcept { destroy(); }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void lock() noexcept {
                const int err = pthread_mutex_lock( mutex() );
                if(0!=err) Libc::Error::Critical(err, "pthread_mutex_lock" );
            }

            virtual void unlock() noexcept {
                const int err = pthread_mutex_unlock( mutex() );
                if(0!=err) Libc::Error::Critical(err, "pthread_mutex_lock" );
            }

            virtual bool tryLock() noexcept {
                return 0 == pthread_mutex_trylock( mutex() );
            }


        private:
            Y_Disable_Copy_And_Assign(SystemMutex);
            Memory::Zombie<pthread_mutex_t> mutex;

            void destroy() noexcept
            {
                (void) pthread_mutex_destroy( mutex() );
            }

        };


    }
}

#endif // defined(Y_BSD)

#if defined(Y_WIN)
namespace Yttrium
{
    namespace Concurrent
    {
    }
}



#endif // defined(Y_WIN)


#include "y/concurrent/nucleus.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/destruct.hpp"

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
        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        static void *          NucleusWorkspace[ Alignment::WordsFor<Nucleus::Code>::Count ];
        static Nucleus::Code * NucleusCode = 0;


        Nucleus:: Nucleus()
        {
            assert(0==NucleusCode);
            try
            {
                System::AtExit::Perform(SelfDestruct,this,LifeTime);
                NucleusCode = new ( Y_BZero(NucleusWorkspace) ) Code();
                if(Verbose) Display("+", CallSign, LifeTime);
            }
            catch(...)
            {
                NucleusCode = 0;
                throw;
            }
        }

        Nucleus:: ~Nucleus() noexcept
        {
            if(Verbose) Display("~", CallSign, LifeTime);
            assert(0!=NucleusCode);
            Destruct(NucleusCode);
            NucleusCode = 0;
            Y_BZero(NucleusWorkspace);
        }

        void Nucleus:: SelfDestruct(void *const args) noexcept
        {
            assert(0!=args);
            Nucleus &nucleus = *static_cast<Nucleus *>(args);
            nucleus.~Nucleus();
        }


        Nucleus & Nucleus:: Instance()
        {
            static void *    workspace[ Alignment::WordsFor<Nucleus>::Count ];
            static Nucleus & nucleus = * new ( Y_BZero(workspace) ) Nucleus();
            return nucleus;
        }

        Lockable & Nucleus:: giant() noexcept
        {
            assert(NucleusCode);
            return NucleusCode->mutex;
        }


    }

    Lockable & Lockable:: Giant()
    {
        static Lockable & _ = Concurrent::Nucleus::Instance().giant();
        return _;
    }

}

