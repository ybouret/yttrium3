
//! \file

#ifndef Y_BCopy_Included
#define Y_BCopy_Included 1

#include "y/libc/block/copy.h"

namespace Yttrium
{

    //! binary copy \param a target \param b source
    template <typename T> inline
    void BCopy( T &a , const T &b) noexcept
    {
        Yttrium_BCopy(&a,&b,sizeof(T));
    }
}

#endif // !Y_BCopy_Included

