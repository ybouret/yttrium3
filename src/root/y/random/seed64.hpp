
//! \file

#ifndef Y_Random_Seed64_Included
#define Y_Random_Seed64_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Random
    {

        struct Seed64
        {
            static uint64_t Get64() noexcept;
            static uint32_t Get32() noexcept;
            static uint16_t Get16() noexcept;
            static uint8_t  Get8()  noexcept;

        };

    }

}

#endif // !Y_Random_Seed64_Included

