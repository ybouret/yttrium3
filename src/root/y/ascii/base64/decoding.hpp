//! \file

#ifndef Y_ASCII_Base64_Decoding_Included
#define Y_ASCII_Base64_Decoding_Included

#include "y/config/compiler.h"
#include "y/ascii/base64/common.hpp"

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
            //! Base64 decoding low-level functions
            //
            //
            //__________________________________________________________________
            struct Decoding
            {
                static const uint8_t LUT[256];          //!< reverse look-up-table, 255 means error
                static const char    Pad = Common::Pad; //!< padding symbol

            };

        }

    }

}

#endif // !Y_ASCII_Base64_Decoding_Included
