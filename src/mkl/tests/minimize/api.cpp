
#include "y/mkl/minimize/api.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/mkl/api/half.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T> static inline
    T F(T x)
    {
        const T xopt(0.2f);
        const T delta = x - xopt;
        const T dy(0.66f);
        const T fac(0.37f);
        const T arg = dy + fac * delta * delta;
        return Sqrt<T>(arg);
    }

    template <typename T> static inline
    void testMin()
    {
        Minimizer<T> minimize;
        minimize.verbose = true;
        while(true)
        {
            Triplet<T> x = { -0.8f, 0 , 0.7f };
            Triplet<T> f = { F<T>(x.a), F<T>(x.b), F<T>(x.c) };
            const T x_opt = minimize.find(F<T>,x,f);
            std::cerr << "x_opt=" << x_opt << std::endl;
            break;
        }
    }
}

Y_UTEST(min_api)
{

    testMin<float>();
    testMin< XReal<long double> >();
    testMin<double>();

}
Y_UDONE()
