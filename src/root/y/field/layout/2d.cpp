

#include "y/field/layout/2d.hpp"

namespace Yttrium
{
    namespace Field
    {
        Layout2D:: Layout2D(const Coord2D lo, const Coord2D up) :
        Layout<Coord2D>(lo,up),
        sub(lower().x,upper().x)
        {
        }

        Layout2D:: Layout2D(const Layout2D &L) noexcept :
        Layout<Coord2D>(L),
        sub(L.sub)
        {
        }

        Layout2D:: ~Layout2D() noexcept
        {
        }

    }

}

