
//! \file

#ifndef Y_Apex_KegBits_Included
#define Y_Apex_KegBits_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //! Bits Data for specific WORD
        template <typename WORD> struct BitsData
        {
            static const size_t Count = sizeof(WORD)*8; //!< number of bits
            static const WORD   Mask[Count];            //!< 2^i
            static const WORD   Not2[Count];            //!< ~Mask
        };

        template<> const uint8_t  BitsData<uint8_t>:: Mask[8];
        template<> const uint16_t BitsData<uint16_t>::Mask[16];
        template<> const uint32_t BitsData<uint32_t>::Mask[32];

        template<> const uint8_t  BitsData<uint8_t>:: Not2[8];
        template<> const uint16_t BitsData<uint16_t>::Not2[16];
        template<> const uint32_t BitsData<uint32_t>::Not2[32];


    }
}

#endif // !Y_Apex_KegBits_Included

