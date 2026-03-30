
//! \file

#ifndef Y_ASCII_Base64_Metrics_Included
#define Y_ASCII_Base64_Metrics_Included

#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace ASCII
    {
        namespace Base64
        {
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


        }
    }

}

#endif // !Y_ASCII_Base64_Metrics_Included
