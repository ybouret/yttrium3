
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    template <typename> class Complex;

    namespace MKL
    {
        //! defining scalar for a given type
        template <typename T> struct ScalarFor
        {
            typedef T Type; //!< default is same type
        };

        //! defining scalar for complexes
        template <typename T> struct ScalarFor< Complex<T> >
        {
            typedef T Type; //!< base type
        };
    }
}

#endif // !Y_MKL_ScalarFor_Included
