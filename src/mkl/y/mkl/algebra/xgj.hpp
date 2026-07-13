
//! \file

#ifndef Y_MKL_Algebra_XGJ_Included
#define Y_MKL_Algebra_XGJ_Included 1

#include "y/container/matrix.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! eXtended Gauss Jordan algorithm
        //
        //
        //______________________________________________________________________
        struct XGJ
        {
            //! apply Gauss-Jordan with row pivoting
            /**
             \param a primary matrix to apply algorithm
             \param b replica matrix (a.k.a "unknown")
             \return number of valid rows
             */
            static size_t Build(Matrix<apq> &a, Matrix<apq> &b);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static apq FindPivot(size_t            &ip,
                                 const Matrix<apq> &a,
                                 const size_t       i);
#endif



        };

    }

}

#endif // !Y_MKL_Algebra_XGJ_Included

