//! \file

#ifndef Y_Calculus_SplitWord_Included
#define Y_Calculus_SplitWord_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Calculus
    {

        struct SplitWord
        {

            template <typename T> struct Make;

        };

        template <> struct SplitWord:: Make<uint8_t>
        {
            static uint8_t * From(uint16_t &x, size_t &n) noexcept;
            static uint8_t * From(uint32_t &x, size_t &n) noexcept;
            static uint8_t * From(uint64_t &x, size_t &n) noexcept;

        };

    }

}

#endif // !Y_Calculus_SplitWord_Included
