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
        dimension(other.dimension),
        hyperSize(other.hyperSize)
        {
        }

        Metrics:: Metrics(const size_t dim) noexcept :
        dimension(dim),
        hyperSize(dimension-1)
        {
            assert(dimension>0);
        }

        const char * Metrics:: HumanReadableQuality(const Quality quality) noexcept
        {
            switch(quality)
            {
                    Y_Return_Named_Case(Degenerate);
                    Y_Return_Named_Case(Fragmental);
                    Y_Return_Named_Case(HyperPlane);
                    Y_Return_Named_Case(TotalSpace);
            }
            return Core::Unknown;
        }

        Metrics::Quality Metrics:: computeQuality(const size_t size) const noexcept
        {
            assert(size<=dimension);
            if(size<=0)         return Degenerate;
            if(size>=dimension) return TotalSpace;
            if(size>=hyperSize) return HyperPlane;
            return                     Fragmental;
        }


    }

}

