#include "y/mkl/algebra/xgj.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(algebra_xgj)
{
    Core::Rand ran;

    Matrix<apq> a(3,3);
    for(size_t i=1;i<=a.rows;++i)
    {
        for(size_t j=1;j<=a.cols;++j)
        {
            a[i][j] = Random::Gen<uint8_t>::Get(ran);
        }
    }
    std::cerr << "a=" << a << std::endl;

    XGJ::Build(a);

}
Y_UDONE()
