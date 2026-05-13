
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    template <typename> class Complex;
    template <typename> class V2D;
    template <typename> class V3D;
    template <typename> class V4D;

    //! helper
#define Y_MKL_DECL_VECTORIAL(CLASS)                  \
template <typename T> struct ScalarFor< CLASS<T> > { \
typedef T         Type;                              \
static const bool Flag = false; }

    namespace MKL
    {
        //! defining scalar for a given type
        template <typename T> struct ScalarFor
        {
            typedef T         Type;        //!< default is same type
            static const bool Flag = true; //!< scalar type
        };


        Y_MKL_DECL_VECTORIAL(Complex); //!< declare vectorial types
        Y_MKL_DECL_VECTORIAL(V2D);     //!< declare vectorial types
        Y_MKL_DECL_VECTORIAL(V3D);     //!< declare vectorial types
        Y_MKL_DECL_VECTORIAL(V4D);     //!< declare vectorial types


        //! helper to select
        template <typename T> struct IsScalar
        {
            static const bool Value = ScalarFor<T>::Flag; //!< alias
        };

    }
}

#endif // !Y_MKL_ScalarFor_Included
