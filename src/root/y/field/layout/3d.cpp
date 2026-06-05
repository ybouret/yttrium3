


#include "y/field/layout/3d.hpp"

namespace Yttrium
{
    namespace Field
    {
        Layout3D:: Layout3D(const Coord3D lo, const Coord3D up) :
        Layout<Coord3D>(lo,up),
        sub( Coord2D(lower().x,lower().y), Coord2D(upper().x,upper().y) )
        {
        }

        Layout3D:: Layout3D(const Layout3D &L) noexcept :
        Layout<Coord3D>(L),
        sub(L.sub)
        {
        }

        Layout3D:: ~Layout3D() noexcept
        {
        }

    }

}

