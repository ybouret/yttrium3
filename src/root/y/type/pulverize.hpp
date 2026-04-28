

//! \file

#ifndef Y_Type_Pulverize_Included
#define Y_Type_Pulverize_Included 1

#include "y/libc/block/zero.h"
#include <cassert>

namespace Yttrium
{

    //! destroy and zero memory \param alive live object
    template <typename T> inline
    void Pulverize(T * const alive) noexcept
    {
        assert(0!=alive);
        alive->~T();
        Yttrium_BZero(alive,sizeof(T));
    }

    //! destroy and zero memory \param alive live object \return zombie object
    template <typename T> inline
    T * Pulverized(T * const alive) noexcept
    {
        assert(0!=alive);
        alive->~T();
        return static_cast<T*>(Yttrium_BZero(alive,sizeof(T)));
    }

}

#endif // !Y_Type_Pulverize_Included
