#include "y/concurrent/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Subdivision:: ~Subdivision() noexcept
        {
        }

        Subdivision:: Subdivision(const size_t sz, const size_t rk) noexcept :
        Member(sz,rk)
        {
        }
        
    }

}
