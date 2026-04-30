#include "y/calculus/non-zero-bits.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        const size_t NonZeroBits::Table[256] =
        {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
        };

        size_t NonZeroBits:: For(const uint8_t &x) noexcept
        {
            return Table[x];
        }

        size_t NonZeroBits:: For(const uint16_t &x) noexcept
        {
            return Table[ uint8_t(x) ] + Table[ uint8_t(x>>8) ];
        }

        size_t NonZeroBits:: For(const uint32_t &x) noexcept
        {
            return Table[ uint8_t(x)     ]
            +      Table[ uint8_t(x>>8)  ]
            +      Table[ uint8_t(x>>16) ]
            +      Table[ uint8_t(x>>24) ];
        }

        size_t NonZeroBits:: For(const uint64_t &x) noexcept
        {
            return Table[ uint8_t(x)     ]
            +      Table[ uint8_t(x>>8)  ]
            +      Table[ uint8_t(x>>16) ]
            +      Table[ uint8_t(x>>24) ]
            +      Table[ uint8_t(x>>32) ]
            +      Table[ uint8_t(x>>40) ]
            +      Table[ uint8_t(x>>48) ]
            +      Table[ uint8_t(x>>56) ];
        }




    }
}
