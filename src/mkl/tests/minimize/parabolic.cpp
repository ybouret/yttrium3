
#include "y/mkl/minimize/parabolic.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"
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
    void testPara()
    {
        Triplet<T> x = { -0.8f, 0 , 0.7f };
        Triplet<T> f = { F<T>(x.a), F<T>(x.b), F<T>(x.c) };
        Parabolic<T> parabolic;
        parabolic.verbose = true;
        for(size_t i=1;i<=1;++i)
        {
            const T w = parabolic.step(F<T>,x,f);
            std::cerr << "w=" << w << std::endl << std::endl;
        }

    }

}
Y_UTEST(min_parabolic)
{
    {
        OutputFile fp("parabolic.data");
        for(double x=-1;x<=1;x+=0.001)
        {
            fp("%g %g\n",x,F<double>(x));
        }
    }


    testPara<float>();

    //const double C = (3.0 - sqrt(5.0))/2;
    //const double R = 1.0 - C;
    //std::cerr << C << " / " << R << std::endl;

    return 0;
    
    testPara< XReal<long double> >();



}
Y_UDONE()

