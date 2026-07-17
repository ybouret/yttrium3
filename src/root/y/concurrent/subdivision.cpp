#include "y/concurrent/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Subdivision:: ~Subdivision() noexcept
        {
        }

        Subdivision:: Subdivision(const size_t sz,
                                  const size_t rk,
                                  Lockable    &lk) noexcept :
        Context(sz,rk,lk),
        entry(0),
        bytes(0)
        {
        }

        Subdivision:: Subdivision(const Context &ctx)  noexcept :
        Context(ctx),
        entry(0),
        bytes(0)
        {
        }
        

    }

}
