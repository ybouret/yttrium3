
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
                Memory::Single<pthread_mutexattr_t> attr;

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

            inline virtual ~SystemMutex() noexcept
            {
                const int err = pthread_mutex_destroy( mutex() );
                if(0!=err) Libc::Error::Critical(err, "pthread_mutex_destroy" );
            }

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

            pthread_mutex_t * operator()(void) noexcept { return mutex(); }

        private:
            Y_Disable_Copy_And_Assign(SystemMutex);
            Memory::Single<pthread_mutex_t> mutex;
        };

    }

}

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! pthread condition wrapper
        //
        //
        //______________________________________________________________________
        class SystemCondition
        {
        public:

            inline SystemCondition() : cond()
            {
                const int err = pthread_cond_init( cond(), 0);
                if(0!=err) throw Libc::Exception(err, "pthread_cond_init" );
            }

            inline void wait(SystemMutex &mutex) noexcept
            {
                const int err = pthread_cond_wait( cond(), mutex() );
                if(0!=err) Libc::Error::Critical(err, "pthread_cond_init" );
            }

            inline void signal()
            {
                const int err = pthread_cond_signal( cond() );
                if(0!=err) Libc::Error::Critical(err, "pthread_cond_signal" );
            }

            inline void broadcast()
            {
                const int err = pthread_cond_broadcast( cond() );
                if(0!=err) Libc::Error::Critical(err, "pthread_cond_signal" );
            }


            inline ~SystemCondition() noexcept
            {
                const int err = pthread_cond_destroy( cond() );
                if(0!=err) Libc::Error::Critical(err, "pthread_cond_destroy" );
            }

        private:
            Y_Disable_Copy_And_Assign(SystemCondition);
            Memory::Single<pthread_cond_t> cond;
        };


    }
}


namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! pthread condition wrapper
        //
        //
        //______________________________________________________________________
        class SystemThread
        {
        public:
            inline SystemThread(Thread &thread) :
            pthr()
            {
                const int err = pthread_create( pthr(), 0, Launch, &thread);
                if(0!=err) throw Libc::Exception(err,"pthread_create");
            }


            inline ~SystemThread() noexcept
            {
                std::cerr << "Waiting for SystemThread" << std::endl;
                void *    res = 0;
                const int err = pthread_join( *pthr(), &res );
                if(0!=err) Libc::Error::Critical(err, "pthread_join");
            }


        private:
            Y_Disable_Copy_And_Assign(SystemThread);
            Memory::Single<pthread_t> pthr;

            static inline void * Launch(void *addr) noexcept
            {
                assert(0!=addr);
                try
                {
                    Thread &self = *static_cast<Thread *>(addr);
                    self.proc(self.args);
                }
                catch(...)
                {

                }
                return 0;
            }
        };

    }

}

