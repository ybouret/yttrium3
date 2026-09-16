

#include "y/mkl/minimize/golden.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/mkl/api/half.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string/env/convert.hpp"
#include "y/core/rand.hpp"

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
    void testGolden(Random::CoinFlip &ran)
    {
        while(true)
        {
            Triplet<T> xx = { getX<T>(ran), getX<T>(ran), getX<T>(ran) }; if( !xx.isOrdered() )     continue;
            Triplet<T> ff = { F(xx.a), F(xx.b), F(xx.c) };                if( !ff.isLocalMinimum()) continue;

            std::cerr << "ini: xx=" << xx << ", ff=" << ff << std::endl;

            bool         verbose = true;
            XML::Log     xml(std::cerr,verbose);
            const size_t cycles = EnvironmentConvert::To<size_t>("CYCLES",1);

            std::cerr << "|_w=" << Fabs<T>(xx.c-xx.a) << std::endl;
            for(size_t i=1;i<=cycles;++i)
            {
                Golden<T>::Step(xml,F<T>,xx,ff);
                std::cerr << "|_w=" << Fabs<T>(xx.c-xx.a) << std::endl;
            }


            break;
        }
    }


}

Y_UTEST(min_golden)
{

    XRealOutput::Mode = XRealOutput::Compact;
    Core::Rand   ran;

    {
        OutputFile fp("golden.dat");
        for(double x=-1.0;x<=1.0;x+=0.001)
        {
            fp("%.15g %.15g\n", x, F<double>(x) );
        }
    }

    testGolden<float>( ran );

}
Y_UDONE()

