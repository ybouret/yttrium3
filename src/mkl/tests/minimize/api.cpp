
#include "y/mkl/minimize/api.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/mkl/api/half.hpp"
#include "y/stream/libc/output.hpp"
#include "y/random/park-miller.hpp"

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

    template <typename T> static
    inline T getX(Random::Uniform32 &ran)
    {
        return (1.0f - 2.0f * ran.to<float>());
    }

    template <typename T> static inline
    void testMin(Random::Uniform32 &ran)
    {
        bool verbose = true;
        XML::Log xml(std::cerr,verbose);
        Minimize::Engine<T> minimize;
        //minimize.verbose = true;
        for(size_t i=1;i<=1;++i)
        {
        TRY:
            Triplet<T> x = { getX<T>(ran), getX<T>(ran), getX<T>(ran) };
            Triplet<T> f = { F<T>(x.a), F<T>(x.b), F<T>(x.c) };
            x.sort(f);
            if(!f.isLocalMinimum()) goto TRY;
            const T x_opt = minimize.find(xml,F<T>,Minimize::Direct,x,f,Minimize::Pedantic);
            std::cerr << "x_opt=" << x_opt << std::endl;
            //break;
        }
    }
}

Y_UTEST(min_api)
{
    Random::ParkMiller ran;

    testMin<float>(ran);
    testMin< XReal<long double> >(ran);
    testMin<double>(ran);

}
Y_UDONE()
