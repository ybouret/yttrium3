
//! \file

#ifndef Y_Swap_Included
#define Y_Swap_Included 1

#include "y/libc/bswap.h"

namespace Yttrium
{
    template <typename T> inline
    void Swap(T &a, T &b)
    {
        const T tmp(a);
        a=b;
        b=tmp;
    }

    template <typename T> inline
    void CoerceSwap(const T &a, const T &b)
    {
        Swap( (T&)a, (T&)b );
    }

    template <typename T> inline
    void BSwap(T &a, T &b) noexcept
    {
        Yttrium_BSwap(&a,&b,sizeof(T));
    }

}

#endif // !Y_Swap_Included
