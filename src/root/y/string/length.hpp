//! \file

#ifndef Y_String_Length_Included
#define Y_String_Length_Included 1

#include "y/config/compiler.h"

namespace Yttrium
{

    template <typename T> static inline
    size StringLength(const T * s) noexcept
    {
        if(!s)
            return 0;
        else
        {
            size_t res = 0;
            while( 0 != *(s++) )
                ++res;
            return res;
        }
    }
}


#endif // !Y_String_Length_Included

