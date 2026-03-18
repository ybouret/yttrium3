#include "y/concurrent/mutex.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        SystemMutex * Nucleus:: acquireSystemMutex()
        {
            assert(data);
            assert(code);
#if defined(Y_BSD)
            return data->mutexes.produce(code->attr);
#endif

#if defined(Y_WIN)
            return data->mutexes.produce();
#endif
        }

        void Nucleus:: releaseSystemMutex(SystemMutex * const mutex) noexcept
        {
            assert(mutex);
            assert(data);
            data->mutexes.recycle(mutex);
        }


    }

}

namespace Yttrium
{
    namespace Concurrent
    {
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
