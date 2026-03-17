
#include "y/ability/collectable.hpp"
#include "y/calculus/gc.hpp"
#include <iostream>

namespace Yttrium
{
    Collectable:: ~Collectable() noexcept
    {
    }

    Collectable:: Collectable() noexcept
    {
    }

    
    void Collectable:: release() noexcept
    {
        gc(All);
    }


    size_t Collectable:: NewSize(const uint8_t amount, const size_t oldSize) noexcept
    {
        const uint8_t keep = (uint8_t)(All - amount);
        return GC::Kept(oldSize,keep);
    }


}
