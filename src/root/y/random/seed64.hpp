
//! \file

#ifndef Y_Random_Seed64_Included
#define Y_Random_Seed64_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //
        //
        //! generating system seed in 64 bits
        //
        //
        //______________________________________________________________________
        struct Seed64
        {
            static uint64_t Get64() noexcept; //!< \return 64 bits seed
            static uint32_t Get32() noexcept; //!< \return compressed 32 bits seed
            static uint16_t Get16() noexcept; //!< \return compressed 16 bits seed
            static uint8_t  Get8()  noexcept; //!< \return compressed 8 bits seed

        };

    }

}

#endif // !Y_Random_Seed64_Included

