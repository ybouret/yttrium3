#include "y/calculus/required-bits.hpp"

namespace Yttrium
{
    namespace Calculus
    {

        const size_t RequiredBits:: Table[256] =
        {
            0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
        };

        size_t RequiredBits:: For(const uint8_t &x) noexcept
        {
            return Table[x];
        }

        size_t RequiredBits:: For(const uint16_t &x) noexcept
        {
            static const uint16_t lim0 = 0x00;
            static const uint16_t lim1 = 0xff;
            if(x<=lim0) return 0;
            if(x<=lim1) return Table[(uint8_t)x];
            return 8+Table[(uint8_t)(x>>8)];
        }

        size_t RequiredBits:: For(const uint32_t &x) noexcept
        {
            static const uint32_t lim0 = 0x00000000;
            static const uint32_t lim1 = 0x000000ff;
            static const uint32_t lim2 = 0x0000ffff;
            static const uint32_t lim3 = 0x00ffffff;
            if(x<=lim0) return 0;
            if(x<=lim1) return    Table[(uint8_t)(x)];
            if(x<=lim2) return  8+Table[(uint8_t)(x>>8)];
            if(x<=lim3) return 16+Table[(uint8_t)(x>>16)];
            return             24+Table[(uint8_t)(x>>24)];
        }

    }

}
