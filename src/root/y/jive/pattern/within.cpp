
#include "y/jive/pattern/within.hpp"
#include "y/swap.hpp"

namespace Yttrium
{

    namespace Jive
    {

        Within:: ~Within() noexcept
        {
        }

        Within:: Within(const Within &other) noexcept :
        lower(other.lower),
        upper(other.upper)
        {
        }

        Within:: Within(const uint8_t lo, const uint8_t up) noexcept :
        lower(lo),
        upper(up)
        {
            if(lower>upper) CoerceSwap(lower,upper);
        }

    }

}

