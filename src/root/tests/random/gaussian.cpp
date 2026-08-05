
#include "y/random/park-miller.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/isaac.hpp"
#include "y/random/gaussian.hpp"

#include "y/mkl/statistics/variance.hpp"
#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace
{
    static inline void checkGaussian(Random::SharedBits &sharedBits)
    {
        Random::Gaussian<double> gran( sharedBits );

        std::cerr << gran->callSign() << std::endl;
        static const size_t n = 100000;
        Vector<double>      r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << gran();

        Cameo::Addition<double> xadd(n);
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "\tave=" << ave << std::endl;
        std::cerr << "\tvar=" << var << std::endl;
        std::cerr << std::endl;
    }
}

Y_UTEST(random_gaussian)
{

    Random::SharedBits ranParkMiller = new Random::ParkMiller();
    Random::SharedBits ranMT19937    = new Random::MT19937()    ;
    Random::SharedBits ranISAAC4     = new Random::ISAAC<4>()   ;
    Random::SharedBits ranISAAC8     = new Random::ISAAC<8>()   ;

    checkGaussian(ranParkMiller);
    checkGaussian(ranMT19937);
    checkGaussian(ranISAAC4);
    checkGaussian(ranISAAC8);

}
Y_UDONE()
