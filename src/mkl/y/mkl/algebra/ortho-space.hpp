
//! \file

#ifndef Y_MKL_OrthoSpace_Included
#define Y_MKL_OrthoSpace_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{

    namespace MKL
    {

        //! compute orthogonal generating space
        struct OrthoSpace
        {
            //! evaluation
            /**
             \param Q output generating space iff success
             \param P basis of row vectors
             \return true iff P was a basis of a strict subspace
             */
            static bool Eval(Matrix<apz> &Q, const Matrix<apz> &P);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename T> static inline
            bool Get(Matrix<apz> &Q, const Matrix<T> &P)
            {
                Matrix<apz> _(CopyOf,P);
                return Eval(Q,_);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }

}

#endif // !Y_MKL_OrthoSpace_Included

