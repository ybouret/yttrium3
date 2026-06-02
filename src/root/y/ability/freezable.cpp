
#include "y/ability/freezable.hpp"


namespace Yttrium
{

    Freezable:: Freezable() noexcept : frozen(false)
    {
    }

    Freezable:: ~Freezable() noexcept
    {
    }

    void Freezable:: freeze() noexcept
    {
        Coerce(frozen) = true;
    }

}
