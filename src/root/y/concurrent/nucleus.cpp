

#include "y/config/platform.h"
#include "y/memory/zombie.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"

#if defined(Y_BSD)
#include <pthread.h>

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //! pthread mutex wrapper
        //
        //______________________________________________________________________
        class SystemMutex
        {
        public:
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


            inline explicit SystemMutex(Attribute &attr) : mutex()
            {
                const int err = pthread_mutex_init( mutex(), *attr );
                if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
            }

            inline virtual ~SystemMutex() noexcept { destroy(); }

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
