

//! \file

#ifndef Y_Calculus_RequiredBits_Included
#define Y_Calculus_RequiredBits_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //! compute required bits to hold a given word
        struct RequiredBits
        {
            static const size_t Table[256]; //!< precomputed 8-bits results
            static size_t For(const uint8_t  &) noexcept; //!< \return bits to hold word
            static size_t For(const uint16_t &) noexcept; //!< \return bits to hold word
            static size_t For(const uint32_t &) noexcept; //!< \return bits to hold word
            static size_t For(const uint64_t &) noexcept; //!< \return bits to hold word

        };

    }
}

#endif // !Y_Calculus_RequiredBits_Included

