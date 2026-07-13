
//! \file

#ifndef Y_MKL_Algebra_XGJ_Included
#define Y_MKL_Algebra_XGJ_Included 1

#include "y/container/matrix.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

        struct XGJ
        {
            static size_t Build(Matrix<apq> &a);

            static apq FindPivot(size_t            &ip,
                                 const Matrix<apq> &a,
                                 const size_t       i);

            


        };

    }

}

#endif // !Y_MKL_Algebra_XGJ_Included

