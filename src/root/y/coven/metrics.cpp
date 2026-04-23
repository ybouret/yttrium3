#include "y/coven/metrics.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Coven
    {
        Metrics:: ~Metrics() noexcept
        {
        }

        Metrics:: Metrics(const Metrics &other) noexcept :
        dimensions(other.dimensions)
        {
        }

        Metrics:: Metrics(const size_t dims) noexcept :
        dimensions(dims)
        {
            assert(dimensions>0);
        }

        
    }

}

