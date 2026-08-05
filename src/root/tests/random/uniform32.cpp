#include "y/random/park-miller.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/isaac.hpp"

#include "y/mkl/statistics/variance.hpp"
#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace
{
    static inline void checkStats(Random::Bits &ran)
    {
        std::cerr << ran.callSign() << std::endl;
        static const size_t n = 100000;
        Vector<double>      r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << ran();

        Cameo::Addition<double> xadd(n);
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "\tave=" << ave << std::endl;
        std::cerr << "\tvar=" << var << std::endl;
        std::cerr << std::endl;
    }
}

Y_UTEST(random_uniform32)
{

    Random::ParkMiller ranParkMiller;
    Random::MT19937    ranMT19937;
    Random::ISAAC<4>   ranISAAC4;
    Random::ISAAC<8>   ranISAAC8;

    checkStats(ranParkMiller);
    checkStats(ranMT19937);
    checkStats(ranISAAC4);
    checkStats(ranISAAC8);

}
Y_UDONE()
