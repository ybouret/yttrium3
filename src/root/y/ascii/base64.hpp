//! \file

#ifndef Y_ASCII_Base64_Included
#define Y_ASCII_Base64_Included

#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace ASCII
    {

        //______________________________________________________________________
        //
        //
        //
        //! Base64 encoding and decoding low-level functions
        //
        //
        //______________________________________________________________________
        struct Base64
        {

            static const char    STD[64];     //!< standard table
            static const char    URL[64];     //!< url table
            static const char    Pad = '=';   //!< padding symbol
            static const uint8_t LUT[256];    //!< reverse look-up-table, 255 means error

            //! return encoding byte for LUT \param C char \return 0:63 if encoding, 255 means error
            static uint8_t Encoding(const char C) noexcept;

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

            //! compute output bytes for given input
            template <size_t INPUT> struct BytesFor
            {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                static const size_t _3 = 3;
                static const size_t q  = INPUT/_3;
                static const size_t r  = INPUT%_3;
                static const size_t n  = q + ( (r>0) ? 1 : 0 );
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
                static const size_t Value = n*4; //!< value
            };

            //! compute output chars for given input
            template <size_t INPUT> struct CharsFor
            {
                static const size_t Required = BytesFor<INPUT>::Value + 1; //!< bytes + '0'
                static const size_t Value    = Alignment::SystemMemory::CeilOf<Required>::Value; //!< valye
            };

        };


    }
}


#endif // !Y_ASCII_Base64_Included

