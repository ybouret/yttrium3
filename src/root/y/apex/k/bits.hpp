
//! \file

#ifndef Y_Apex_KegBits_Included
#define Y_Apex_KegBits_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {

        template <typename WORD> struct BitsData
        {
            static const size_t Count = sizeof(WORD)*8;
            static const WORD Table[Count];
        };

        template<> const uint8_t  BitsData<uint8_t>::Table[8];
        template<> const uint16_t BitsData<uint16_t>::Table[16];
        template<> const uint32_t BitsData<uint32_t>::Table[32];

    }
}

#endif // !Y_Apex_KegBits_Included

