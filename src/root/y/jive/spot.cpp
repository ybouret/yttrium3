#include "y/jive/spot.hpp"
//#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Spot:: ~Spot() noexcept
        {
        }

        Spot:: Spot(const Spot &spot) noexcept :
        title(spot.title),
        line(spot.line),
        column(spot.column)
        {
        }




    }
}
