
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
                void *    res = 0;
                const int err = pthread_join( *pthr(), &res );
                if(0!=err) Libc::Error::Critical(err, "pthread_join");
            }


            bool assign(const size_t cpu) noexcept;


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

#if defined Y_THREAD_AFFINITY
#error "Y_THREAD_AFFINITY shouldn't be defined"
#endif

#if defined(Y_Darwin)
#define Y_THREAD_AFFINITY 1

#if defined(Y_GNU)
#define _Static_assert static_assert
#endif

#include <mach/thread_policy.h>
#include <mach/thread_act.h>

namespace Yttrium
{
    namespace Concurrent
    {

        bool SystemThread::assign(const size_t j) noexcept
        {
            thread_affinity_policy_data_t policy_data = { int(j) };
            mach_port_t                   mach_thread = pthread_mach_thread_np(*pthr());
            const int                     mach_result = thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy_data, THREAD_AFFINITY_POLICY_COUNT);
            if (KERN_SUCCESS != mach_result)
            {
                const Mach::Exception excp(mach_result, "thread_policy_set");
                excp.display(std::cerr);
                return false;
            }
            else
            {
                return true;
            }

        }

    }

}

#endif // defined(Y_Darwin)



#if defined(Y_Linux)|| defined(Y_FreeBSD)
#   define Y_THREAD_AFFINITY 1
#   if defined(Y_FreeBSD)
#      include <pthread_np.h>
#      define Y_CPU_SET cpuset_t
#   else
#      define Y_CPU_SET cpu_set_t
#   endif

namespace Yttrium
{
    namespace Concurrent
    {
        bool   SystemThread::assign(const size_t j) noexcept
        {
            Y_CPU_SET the_cpu_set;
            CPU_ZERO(&the_cpu_set);
            CPU_SET(j, &the_cpu_set);
            const int err = pthread_setaffinity_np(*pthr(), sizeof(Y_CPU_SET), &the_cpu_set);
            if (err != 0)
            {
                const Libc::Exception excp(err, "pthread_setaffinity_np");
                excp.diplay(std::cerr);
                return false;
            }
            else
            {
                return true;
            }
        }

    }

}

#endif // defined(Y_Linux)|| defined(Y_FreeBSD)

#if defined(Y_SunOS)
#   define Y_THREAD_AFFINITY 1
#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>

namespace Yttrium
{
    namespace Concurrent
    {
        bool SystemThread::assign(const size_t j) noexcept
        {
            const int res = processor_bind(P_LWPID, idtype_t(*pthr()), j, NULL);
            if (0 != res)
            {
                const Exception excp("processor_bind failure");
                excp.display(std::cerr);
                return false;
            }
            else
            {
                return true;
            }
        }
    }

}

#endif // defined(Y_SunOS)


#if ! defined(Y_THREAD_AFFINITY)
#warning "No Thread Affinity"
namespace Yttrium
{
    namespace Concurrent
    {
        bool SystemThread::assign(const size_t) noexcept
        {
            const Exception excp("No Thread Affinity");
            excp.display();
            return false;
        }
    }
}

#endif // ! defined(Y_THREAD_AFFINITY)
