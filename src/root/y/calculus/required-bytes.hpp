
//! \file

#ifndef Y_Calculus_RequiredBytes_Included
#define Y_Calculus_RequiredBytes_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        struct RequiredBytes
        {
            static size_t For(const uint8_t  &) noexcept;
            static size_t For(const uint16_t &) noexcept;
            static size_t For(const uint32_t &) noexcept;
            static size_t For(const uint64_t &) noexcept;
        };

    }
}

#endif // !Y_Calculus_RequiredBytes_Included

