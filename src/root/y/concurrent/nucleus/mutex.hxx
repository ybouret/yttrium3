#include "y/concurrent/mutex.hpp"

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

        void Mutex:: lock() noexcept
        {
            assert(handle);
            handle->lock();
        }

        void Mutex:: unlock() noexcept
        {
            assert(handle);
            handle->unlock();
        }

        bool Mutex:: tryLock() noexcept
        {
            assert(handle);
            return handle->tryLock();
        }

    }
}
