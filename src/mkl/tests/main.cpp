#include "y/utest/driver.hpp"


Y_UTEST_DECL(5)
{
    Y_UTEST(algebra_rank);
    Y_UTEST(algebra_mmul);
    Y_UTEST(algebra_lu);
    Y_UTEST(algebra_adjoint);
    Y_UTEST(algebra_ortho_space);
    Y_UTEST(algebra_tridiag);
    Y_UTEST(algebra_cyclic);
    Y_UTEST(algebra_svd);
    Y_UTEST(algebra_xgj);

    Y_UTEST(chem);

    Y_UTEST(zroot);

    Y_UTEST(min_parabolic);
    Y_UTEST(min_api);

    Y_UTEST(ode_rk4);
    Y_UTEST(ode_expl);

    Y_UTEST(tao_device);
    Y_UTEST(tao2);

}
Y_UTEST_EXEC()
