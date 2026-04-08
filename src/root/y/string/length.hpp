//! \file

#ifndef Y_String_Length_Included
#define Y_String_Length_Included 1

#include "y/config/compiler.h"

namespace Yttrium
{

    template <typename T> static inline
    size_t StringLength(const T * s) noexcept
    {
        if(!s)
            return 0;
        else
        {
            const T * const t = s;
            while( 0 != *s )
                ++s;
            return s-t;
        }
    }
}


#endif // !Y_String_Length_Included

