#include "y/concurrent/api/context.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        Context:: Context(const size_t sz,
                          const size_t rk,
                          Lockable    &lk) noexcept :
        Member(sz,rk),
        sync(lk)
        {

        }

        Context:: Context(Lockable    &lk) noexcept :
        Member(1,0),
        sync(lk)
        {

        }

        Context:: ~Context() noexcept
        {
        }
        
    }

}
