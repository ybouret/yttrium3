#include "y/concurrent/condition.hpp"
#include "y/concurrent/nucleus.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {
        static SystemCondition* AcquireSystemCondition()
        {
            static Nucleus &nucleus = Nucleus::Instance();
            return nucleus.acquireSystemCondition();
        }

        Condition:: Condition() : handle( AcquireSystemCondition() )
        {
            assert(handle);
        }

        Condition:: ~Condition() noexcept
        {
            static Nucleus &nucleus = Nucleus::Location();
            nucleus.releaseSystemCondition(handle);
            Coerce(handle) = 0;
        }
        


    }

}
