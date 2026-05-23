
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
            static bool Eval(Matrix<apz> &Q, const Matrix<apz> &P);

            template <typename T> static inline
            bool Get(Matrix<apz> &Q, const Matrix<T> &P)
            {
                Matrix<apz> _(CopyOf,P);
                return Eval(Q,_);
            }

        };
    }

}

#endif // !Y_MKL_OrthoSpace_Included

