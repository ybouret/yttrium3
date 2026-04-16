
//! \file

#ifndef Y_Apex_Types_Included
#define Y_Apex_Types_Included 1

#include "y/config/compiler.h"

namespace Yttrium
{
    namespace Apex
    {
        typedef uint64_t natural_t; //!< alias
        typedef int64_t  integer_t; //!< alias
    }

    //! light-weight fraction
    struct Fraction {
        Apex::natural_t numer; //!< numerator
        Apex::natural_t denom; //!< denominator
    };


}

#endif // !Y_Apex_Types_Included

