
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    template <typename> class Complex;

    namespace MKL
    {
        template <typename T> struct ScalarFor
        {
            typedef T Type;
        };

        template <typename T> struct ScalarFor< Complex<T> >
        {
            typedef T Type;
        };
    }
}

#endif // !Y_MKL_ScalarFor_Included
