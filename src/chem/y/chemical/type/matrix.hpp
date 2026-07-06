
//! \file

#ifndef Y_Chemical_Matrix_Included
#define Y_Chemical_Matrix_Included 1

#include "y/mkl/xreal.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Matrix<unsigned> UMatrix;
        typedef Matrix<int>      IMatrix;
        typedef Matrix<xreal_t>  XMatrix;
    }

}

#endif // !Y_Chemical_Matrix_Included

