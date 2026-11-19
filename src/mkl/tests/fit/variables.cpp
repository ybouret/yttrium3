#include "y/mkl/fit/variables.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

#include "y/container/matrix.hpp"

using namespace Yttrium;
using namespace MKL;


Y_UTEST(fit_variables)
{


    Fit::Variables       vars;
    const Fit::Variable &D1 = vars("D1");
    const Fit::Variable &D2 = vars("D2");
    const Fit::Variable &t0 = vars("t0");

    Y_PRINTV(vars);

    {
        Fit::Variables v1;
        v1("D",D1);
        Y_PRINTV(v1);

        v1 << t0;
        Y_PRINTV(v1);
        {
            const Fit::Variables cpy1 = v1;
            Y_PRINTV(cpy1);
        }
        v1 = vars;
        Y_PRINTV(v1);
    }

    std::cerr << std::endl;
    Y_PRINTV(vars);
    Vector<size_t>          vec;
    const Readable<size_t> &cst = vec;
    vec << 1 << 2 << 3;

    Y_PRINTV(D1[vec]);
    Y_PRINTV(D2[vec]);
    Y_PRINTV(t0[vec]);
    Y_PRINTV(D1[cst]);
    Y_PRINTV(D2[cst]);
    Y_PRINTV(t0[cst]);

    Matrix<size_t> m(3,3);
    for(size_t i=1;i<=m.rows;++i)
    {
        for(size_t j=1;j<=m.cols;++j)
        {
            m[i][j] = i+j;
        }

    }
    Y_PRINTV(D1[m]);
    Y_PRINTV(D2[m]);
    Y_PRINTV(t0[m]);


}
Y_UDONE()

