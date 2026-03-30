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
            static const char    STD[64];
            static const char    URL[64];
            static const char    Pad = '=';
            static const uint8_t Byte[256];

            static uint8_t Encoding(const char C) noexcept;
            static void    Encode1(char * const out, const uint8_t b0, const bool pad = true, const char * const table = STD) noexcept;
            static void    Encode2(char * const out, const uint8_t b0, const uint8_t b1, const bool pad = true, const char * const table = STD) noexcept;
            static void    Encode3(char * const out, const uint8_t b0, const uint8_t b1, const uint8_t b2, const char * const table = STD) noexcept;

        };
    }
}


#endif // !Y_ASCII_Base64_Included

