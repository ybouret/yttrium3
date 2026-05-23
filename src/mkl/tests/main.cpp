#include "y/utest/driver.hpp"


Y_UTEST_DECL(4)
{
    Y_UTEST(algebra_mmul);
    Y_UTEST(algebra_lu);
    Y_UTEST(algebra_adjoint);
    Y_UTEST(algebra_ortho_space);
    Y_UTEST(algebra_tridiag);

    Y_UTEST(chem);
    
}
Y_UTEST_EXEC()
