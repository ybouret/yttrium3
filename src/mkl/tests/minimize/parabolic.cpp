
#include "y/mkl/minimize/parabolic.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/mkl/api/half.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/api/almost-equal.hpp"
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

    template <typename T> static inline
    void testPara()
    {
        bool         verbose = true;
        XML::Log     xml(std::cerr,verbose);
        const size_t cycles = EnvironmentConvert::To<size_t>("CYCLES",1);

        Triplet<T>   x = { -0.8f, 0 , 0.7f };
        Triplet<T>   f = { F<T>(x.a), F<T>(x.b), F<T>(x.c) };
        Parabolic<T> parabolic;
        for(size_t i=1;i<=cycles;++i)
        {
            std::cerr << "[cycle = " << i << "]" << std::endl;
            parabolic.step(xml,F<T>,x,f);
            const T w = x.c-x.a;
            std::cerr << "w=" << w <<  " / " << x << " => " << f << std::endl;

            bool f_ok = false;
            if( AlmostEqual<T>::Are(f.a,f.b) && AlmostEqual<T>::Are(f.b,f.c) )
            {
                std::cerr << "\tf converged" << std::endl;
                f_ok = true;
            }

            bool x_ok = false;
            if( AlmostEqual<T>::Are(x.a,x.b) && AlmostEqual<T>::Are(x.b,x.c) )
            {
                std::cerr << "\tx converged" << std::endl;
                x_ok = true;
            }

            if(f_ok || x_ok) break;
        }
    }


}
Y_UTEST(min_parabolic)
{

    testPara<float>();
    //testPara< XReal<long double> >();
    
}
Y_UDONE()

