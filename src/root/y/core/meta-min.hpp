

//! \file

#ifndef Y_Core_MetaMax_Included
#define Y_Core_MetaMax_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    //! choice of minimum value
    template <size_t A, size_t B>
    struct MetaMin
    {
        static const size_t Value = A<B ? A : B; //!< result
    };


}

#endif // !Y_Core_MetaMax_Included

