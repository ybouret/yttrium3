#include "y/concurrent/thread.hpp"
#include "y/concurrent/nucleus.hpp"

#include <iostream>

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
            std::cerr << "+Thread" << std::endl;

        }

        Thread & Thread:: self() noexcept { return *this; }

        Thread:: ~Thread() noexcept
        {
            static Nucleus & nucleus = Nucleus::Location();
            std::cerr << "~Thread" << std::endl;
            nucleus.releaseSystemThread(impl);
            Coerce(impl) = 0;
            Coerce(proc) = 0;
            Coerce(args) = 0;
        }


    }

}

