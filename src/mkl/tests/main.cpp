#include "y/utest/driver.hpp"


Y_UTEST_DECL(4)
{
    Y_UTEST(algebra_rank);
    Y_UTEST(algebra_mmul);
    Y_UTEST(algebra_lu);
    Y_UTEST(algebra_adjoint);
    Y_UTEST(algebra_ortho_space);
    Y_UTEST(algebra_tridiag);
    Y_UTEST(algebra_cyclic);
    Y_UTEST(algebra_svd);

    Y_UTEST(chem);

    Y_UTEST(zroot);
    Y_UTEST(min_parabolic);
    
}
Y_UTEST_EXEC()
