
//! \file

#ifndef Y_ASCII_Base64_Encoding_Included
#define Y_ASCII_Base64_Encoding_Included

#include "y/ascii/base64/common.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace ASCII
    {


        namespace Base64
        {

            //__________________________________________________________________
            //
            //
            //
            //! Base64 encoding low-level functions
            //
            //
            //__________________________________________________________________
            struct Encoding
            {
                static const char STD[64];           //!< standard table
                static const char URL[64];           //!< url table
                static const char Pad = Common::Pad; //!< padding symbol

                //! return encoding byte for LUT \param C char \return 0:63 if encoding, 255 means error
                static uint8_t GetByte(const char C) noexcept;

                //! encoding one byte in two or four chars
                /**
                 \param out output[2|4]
                 \param b0  byte to encode
                 \param pad if true, append '==' to output
                 \param table table to encode from
                 */
                static void    Encode1(char * const out, const uint8_t b0, const bool pad = true, const char * const table = STD) noexcept;

                //! encoding two bytes in three or four chars
                /**
                 \param out    output[3|4]
                 \param b0     byte to encode
                 \param b1     byte to encode
                 \param pad    if true, append '=' to output
                 \param table table to encode from
                 */
                static void    Encode2(char * const out, const uint8_t b0, const uint8_t b1, const bool pad = true, const char * const table = STD) noexcept;

                //! encoding three bytes in four chars
                /**
                 \param out    output[4]
                 \param b0     byte to encode
                 \param b1     byte to encode
                 \param b2     byte to encode
                 \param table table to encode from
                 */
                static void    Encode3(char * const out, const uint8_t b0, const uint8_t b1, const uint8_t b2, const char * const table = STD) noexcept;

                //! encoding bytes
                /**
                 \param output large enough output
                 \param input  input[lenght]
                 \param length number of bytes to encode
                 \param pad    padding
                 \param table  table to encode from
                 \return output size
                 */
                static size_t Encode(char * output, const uint8_t * input, const size_t length, const bool pad = true, const char * const table = STD) noexcept;
            };


        }
    }
}


#endif // !Y_ASCII_Base64_Encoding_Included

