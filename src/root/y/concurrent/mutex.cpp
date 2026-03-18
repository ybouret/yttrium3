#include "y/concurrent/mutex.hpp"
#include "y/concurrent/nucleus.hpp"
#include <cassert>

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

       
    }

}

