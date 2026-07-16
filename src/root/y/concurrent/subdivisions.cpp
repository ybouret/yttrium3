#include "y/concurrent/subdivisions.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Subdivisions:: Subdivisions(const size_t n) noexcept : ncpu(n)
        {
            assert(ncpu>0);
        }

        Subdivisions:: ~Subdivisions() noexcept
        {
            
        }

    }

}
