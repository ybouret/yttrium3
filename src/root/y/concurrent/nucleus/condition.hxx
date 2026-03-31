
namespace Yttrium
{
    namespace Concurrent
    {
        SystemCondition * Nucleus:: acquireSystemCondition()
        {
            assert(data);
            return data->conditions.produce();
        }

        void Nucleus:: releaseSystemCondition(SystemCondition * const cond) noexcept
        {
            assert(cond);
            assert(data);
            data->conditions.recycle(cond);
        }

    }

}

#include "y/concurrent/condition.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        void Condition:: signal() noexcept
        {
            assert(handle);
            handle->signal();
        }

        void Condition:: broadcast() noexcept
        {
            assert(handle);
            handle->broadcast();
        }

        void Condition:: wait(Mutex &mutex) noexcept
        {
            assert(handle);
            handle->wait(*mutex.handle);
        }
    }
}
