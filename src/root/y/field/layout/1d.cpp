
#include "y/field/layout/1d.hpp"

namespace Yttrium
{
    namespace Field
    {
        Layout1D:: Layout1D(const Coord1D lo, const Coord1D up) :
        Layout<Coord1D>(lo,up)
        {
        }

        Layout1D:: Layout1D(const Layout1D &L) noexcept :
        Layout<Coord1D>(L)
        {
        }

        Layout1D:: ~Layout1D() noexcept
        {
        }

    }

}

