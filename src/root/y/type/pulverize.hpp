

//! \file

#ifndef Y_Type_Pulverize_Included
#define Y_Type_Pulverize_Included 1

#include "y/libc/block/zero.h"
#include <cassert>

namespace Yttrium
{

    template <typename T> inline
    void Pulverize(T * const obj) noexcept
    {
        assert(0!=obj);
        obj->~T();
        Yttrium_BZero(obj,sizeof(T));
    }

    template <typename T> inline
    T * Pulverized(T * const obj) noexcept
    {
        assert(0!=obj);
        obj->~T();
        return static_cast<T*>(Yttrium_BZero(obj,sizeof(T)));
    }

}

#endif // !Y_Type_Pulverize_Included
