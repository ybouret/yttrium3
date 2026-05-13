
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
            typedef T         Type;        //!< default is same type
            static const bool Flag = true; //!< scalar type
        };

        //! defining scalar for complexes
        template <typename T> struct ScalarFor< Complex<T> >
        {
            typedef T         Type;         //!< base type
            static const bool Flag = false; //!< not a scalar type
        };

        template <typename T> struct IsScalar
        {
            static const bool Value = ScalarFor<T>::Flag;
        };

    }
}

#endif // !Y_MKL_ScalarFor_Included
