#include "y/field/layout/4d.hpp"

namespace Yttrium
{
    namespace Field
    {
        Layout4D:: Layout4D(const Coord4D lo, const Coord4D up) :
        Layout<Coord4D>(lo,up),
        sub(Coord3D(lower().x,lower().y,lower().z),
            Coord3D(upper().x,upper().y,upper().z) )
        {
        }

        Layout4D:: Layout4D(const Layout4D &L) noexcept :
        Layout<Coord4D>(L),
        sub(L.sub)
        {
        }

        Layout4D:: ~Layout4D() noexcept
        {
        }

    }

}

