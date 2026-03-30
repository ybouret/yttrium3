//! \file

#ifndef Y_ASCII_Base64_Included
#define Y_ASCII_Base64_Included

#include "y/config/compiler.h"

namespace Yttrium
{
    namespace ASCII
    {

        struct Base64
        {
            static const char STD[64];
            static const char URL[64];
            static const char Pad = '=';
            static void Encode1(char * const out, const uint8_t b0, const bool pad = true, const char * const table = STD) noexcept;
        };
    }
}


#endif // !Y_ASCII_Base64_Included

