//! \file

#ifndef Y_Swap_Included
#define Y_Swap_Included 1

#include "y/libc/bswap.h"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //! swap types by copy/assign
    /**
     \param a first value
     \param b second value
     */
    //__________________________________________________________________________
    template <typename T> inline
    void Swap(T &a, T &b)
    {
        const T tmp(a);
        a=b;
        b=tmp;
    }

    //__________________________________________________________________________
    //
    //! force swap by coerced copy/assign
    /**
     \param a first value
     \param b second value
     */
    //__________________________________________________________________________
    template <typename T> inline
    void CoerceSwap(const T &a, const T &b)
    {
        Swap( (T&)a, (T&)b );
    }

    //__________________________________________________________________________
    //
    //! binary swap of two type
    /**
     \param a first value
     \param b second value
     */
    //__________________________________________________________________________
    template <typename T> inline
    void BSwap(T &a, T &b) noexcept
    {
        Yttrium_BSwap(&a,&b,sizeof(T));
    }

}

#endif // !Y_Swap_Included
