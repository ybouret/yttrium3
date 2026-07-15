#include "y/concurrent/thread.hpp"
#include "y/concurrent/nucleus.hpp"


namespace Yttrium
{
    namespace Concurrent
    {

        static inline SystemThread * AcquireSystemThread(Thread &thread)
        {
            static Nucleus & nucleus = Nucleus::Instance();
            return nucleus.acquireSystemThread(thread);
        }

        Thread:: Thread(Thread::Proc threadProc, void * const threadArgs) :
        proc(threadProc),
        args(threadArgs),
        impl( AcquireSystemThread( self() ) )
        {

        }

        Thread & Thread:: self() noexcept { return *this; }

        Thread:: ~Thread() noexcept
        {
            static Nucleus & nucleus = Nucleus::Location(); assert(impl);
            nucleus.releaseSystemThread(impl);
            Coerce(impl) = 0;
            Coerce(proc) = 0;
            Coerce(args) = 0;
        }

        bool Thread:: assign(const size_t cpu) noexcept
        {
            assert(impl);
            return Nucleus::Assign(*impl,cpu);
        }
    }

}



