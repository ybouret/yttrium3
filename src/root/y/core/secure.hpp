

//! \file

#ifndef Y_Core_Secure_Included
#define Y_Core_Secure_Included 1

#include "y/swap.hpp"
#include "y/core/clamp.hpp"

namespace Yttrium
{


    //__________________________________________________________________________
    //
    //! inline secure between two values
    /**
     \param lower lower bound
     \param value value to test
     \param upper upper bound
     \return clamped value
     */
    //__________________________________________________________________________
    template <typename T> inline
    T Secure(T lower, const T value, T upper)
    {
        if(upper<lower) Swap(lower,upper);
        return Clamp(lower,value,upper);
    }
}

#endif // !Y_Core_Secure_Included
