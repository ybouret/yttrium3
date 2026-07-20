#include "y/ink/zero-flux.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Ink
    {

        ZeroFlux:: ~ZeroFlux() noexcept
        {
        }

        ZeroFlux:: ZeroFlux(const unit_t n) noexcept :
        count( n ),
        twice( 2*count-1 )
        {
			assert(count >= 0);
        }

        ZeroFlux:: ZeroFlux(const ZeroFlux &z) noexcept :
        count( z.count ),
        twice( z.twice )
        {
        }

        unit_t ZeroFlux::operator[](const unit_t indx) const noexcept
        {
            if(indx<0)
                return (*this)[-indx];
            else
            {
                if(indx>=count)
                {
                    return (*this)[twice-indx];
                }
                else
                    return indx;
            }
        }

    }

}

