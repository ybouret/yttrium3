

//! \file

#ifndef Y_Calculus_RequiredBits_Included
#define Y_Calculus_RequiredBits_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        struct RequiredBits
        {
            static const size_t Table[256];
            static size_t For(const uint8_t  &) noexcept;
            static size_t For(const uint16_t &) noexcept;
            static size_t For(const uint32_t &) noexcept;
            static size_t For(const uint64_t &) noexcept;

        };

    }
}

#endif // !Y_Calculus_RequiredBits_Included

