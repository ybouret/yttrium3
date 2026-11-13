#include "y/mkl/interpolation/continuous.hpp"
#include "y/mkl/interpolation/polynomial.hpp"
#include "y/mkl/interpolation/rational.hpp"

#include "y/container/cxx/light-array.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace MKL;


namespace
{
    template <typename FUNCTION>
    static inline
    void saveInterp(const char * const fileName, FUNCTION &F)
    {
        OutputFile fp(fileName);
        for(float x=0.5f; x<=6.5f; x += 0.01f)
        {
            fp("%g %g\n", x, F(x));
        }
    }
}

Y_UTEST(interpolation_continuous)
{

    const float x[] = { 1,        2,      3,     4,      5,    6 };
    const float y[] = { 0.1f, -0.2f, -0.15f, 0.12f,  0.33f, 0.5f };

    Y_ASSERT( sizeof(x) ==  sizeof(y) );
    const size_t n = sizeof(x)/sizeof(x[0]);
    const LightArray<float> xa((float *)x,n);
    const LightArray<float> ya((float *)y,n);


    {
        OutputFile fp("interp-data.txt");
        for(size_t i=0;i<n;++i) fp("%g %g\n", x[i], y[i]);
    }

    {
        ContinuousInterpolation<float,PolynomialInterpolation> F(xa,ya);
        saveInterp("interp-pol.txt",F);
    }

    {
        ContinuousInterpolation<float,RationalInterpolation> F(xa,ya);
        saveInterp("interp-rat.txt",F);
    }


}
Y_UDONE()


