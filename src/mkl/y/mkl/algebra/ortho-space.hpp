
//! \file

#ifndef Y_MKL_OrthoSpace_Included
#define Y_MKL_OrthoSpace_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{

    namespace MKL
    {

        struct OrthoSpace
        {
            static bool Compute(Matrix<apz> &Q, const Matrix<apz> &P);

            template <typename T> static inline
            bool Of(Matrix<apz> &Q, const Matrix<T> &P)
            {
                Matrix<apz> _(CopyOf,P);
                return Compute(Q,_);
            }

        };
    }

}

#endif // !Y_MKL_OrthoSpace_Included

