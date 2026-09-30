#include "y/mkl/minimize/quadratic.hpp"

#include "y/utest/run.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/core/rand.hpp"
#include "y/string/env/convert.hpp"

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

    template <typename T>
    static inline T getX(Random::CoinFlip &ran)
    {
        const float u = ran.uniform<float>();
        return 1.0f - (u+u);
    }

    template <typename T> static inline
    void testQuadratic(Quadratic<T>     & Q,
                       Random::CoinFlip & ran)
    {
        const size_t iter   = EnvironmentConvert::To<size_t>("ITER",1);
        const size_t cycles = EnvironmentConvert::To<size_t>("CYCLE",0);
        size_t       count  = 0;
        while(true)
        {
            Triplet<T> xx = { getX<T>(ran), getX<T>(ran), getX<T>(ran) }; if( !xx.isOrdered() )     continue;
            Triplet<T> ff = { F(xx.a), F(xx.b), F(xx.c) };                if( !ff.isLocalMinimum()) continue;

            std::cerr << "ini: xx=" << xx << ", ff=" << ff << std::endl;

            bool         verbose = true;
            XML::Log     xml(std::cerr,verbose);

            const T xopt = Q.find(xml, F<T>, xx, ff, cycles);
            std::cerr << "xopt=" << xopt << ": Fopt=" << ff.b << std::endl;
            if(++count>=iter)
                break;
        }
    }


}

Y_UTEST(min_quadratic)
{

    XRealOutput::Mode = XRealOutput::Compact;
    Core::Rand   ran;

    QuadraticStep::Trace = true;

    Quadratic<float>  q;
    testQuadratic(q,ran);
}
Y_UDONE()

