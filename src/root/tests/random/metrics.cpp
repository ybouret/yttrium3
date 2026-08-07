#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/mkl/numeric.hpp"

#include "y/format/hexadecimal.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace Random
    {


    }

}

using namespace Yttrium;

namespace
{
    template <typename T>
    void computeMetrics()
    {
        static const T eps   = MKL::Numeric<T>::EPSILON;
        static const T half  = 0.5f;
        static const T one   = 1;
        static const T top32 = half/eps-one;
        static const T two   = 2;
        static const T top32Shift = std::floor( std::log(top32) / std::log(2) );
        Y_PRINTV(eps);
        Y_PRINTV(top32);
        Y_PRINTV(top32Shift);

        std::cerr << std::endl;
    }
}


Y_UTEST(random_metrics)
{
    Core::Rand ran;
    computeMetrics<float>();
    computeMetrics<double>();
    computeMetrics<long double>();

    static const double numer = 4294967295.5;
    static const double denom = 4294967296.0;
    const double alpha = 0.5 / denom;
    const double beta  = numer/denom;
    std::cerr << alpha << " " << 1.0-beta << " / " << MKL::Numeric<double>::EPSILON << std::endl;


}
Y_UDONE()

