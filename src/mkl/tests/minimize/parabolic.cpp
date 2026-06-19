
#include "y/mkl/minimize/parabolic.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T> static inline
    T F(T x)
    {
        const T xopt(0.2f);
        const T delta = x - xopt;
        const T one(1.0f);
        const T fac(0.37f);
        const T arg = one + fac * delta * delta;
        return Sqrt<T>(arg);
    }

    template <typename T> static inline
    void testPara()
    {
        Triplet<T> x = { -1, 0 ,1 };
    }

}
Y_UTEST(min_parabolic)
{

    testPara<float>();

    testPara< XReal<long double> >();

}
Y_UDONE()

