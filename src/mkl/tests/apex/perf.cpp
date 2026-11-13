#include "y/apex/k/dft.hpp"
#include "y/apex/k/mul.hpp"
#include "y/apex/k/cmp.hpp"

#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/format/human-readable.hpp"
#include "y/ascii/convert.hpp"
#include "y/system/wall-time.hpp"

#include "y/format/percent.hpp"

#include "y/apex/rational.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/min.hpp"
#include "y/format/decimal.hpp"

#include "y/mkl/statistics/variance.hpp"
#include "y/mkl/statistics/average.hpp"
#include "y/core/hsort.hpp"
#include "y/mkl/root/zbis.hpp"

#include "y/mkl/interpolation/continuous.hpp"
#include "y/mkl/interpolation/polynomial.hpp"


using namespace Yttrium;
using namespace Apex;
using namespace MKL;

namespace
{




    static const size_t WarmUp  = 100;
    static const size_t Storage = 1024 * 1024;


    template <typename WORD, typename CORE> static inline
    double CompareDFT(double &dftScore, double &mulScore, const size_t nbits)
    {
        typedef Keg<WORD> KegType;
        (std::cerr << "\tDFT(" << std::setw(4) << nbits << " bits) -- " << sizeof(WORD) * 8 << "-bits | " << sizeof(CORE) * 8 << "-bits: " << std::endl).flush();

        Core::Rand              ran;
        System::WallTime        chrono;
        Vector<double>          rho(WithAtLeast,Storage);
        Cameo::Addition<double> xadd(Storage);
        apn dftSum;
        apn mulSum;
        apn count=0;
        double rhoAve = -1;
        while (true)
        {
            ++count;

            const AutoPtr< KegType > lhs = KegType::MakeRandom(ran, nbits);  assert(lhs.isValid()); assert(nbits == lhs->bits);
            const AutoPtr< KegType > rhs = KegType::MakeRandom(ran, nbits);  assert(rhs.isValid()); assert(nbits == rhs->bits);

            // gather timings
            uint64_t                 m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > dft = KegDFT::Compute(*lhs, *rhs);
            {
                const uint64_t ell = System::WallTime::Ticks() - m64;
                dftSum += ell;
            }

            m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > mul = KegMul::Compute<WORD, CORE>(lhs->word, lhs->words, rhs->word, rhs->words);
            {
                const uint64_t ell = System::WallTime::Ticks() - m64;
                mulSum += ell;
            }

            if(true)
            {
                Y_ASSERT( __Zero__ == KegCmp::ResultFor(*mul,*dft) );
            }

            const apq dftAve = dftSum / count; dftScore = dftAve.ratio<double>();
            const apq mulAve = mulSum / count; mulScore = mulAve.ratio<double>();

            {
                const apq apRho(mulSum,dftSum);
                rho << apRho.ratio<double>(); assert( count == rho.size() );
            }



            if (count < WarmUp)
                continue;

            rhoAve              = MKL::Statistics::Average::Of(rho,xadd);
            const double rhoVar = MKL::Statistics::Variance::Of(rho,rhoAve,xadd);
            const double rhoErr = std::sqrt( rhoVar / (double) rho.size() );

            if(rhoErr<1e-2)
            {
                std::cerr << "\t" << rhoAve << " | err=" << rhoErr << std::endl;
                return rhoAve;
            }

        };

    }

    

}

#include "y/stream/libc/output.hpp"

Y_UTEST(apex_perf)
{

    OutputFile::Overwrite("apex-mul.dat");
    static const size_t one=1;
    Vector<double> x,y;
    for(unsigned p=16;p>=6;--p)
    {
        const size_t bits = one<<p;
        double       dft  = 0;
        double       mul  = 0;
        const double rho  = std::log( CompareDFT<uint32_t,uint64_t>(dft,mul,bits) );
        OutputFile     fp("apex-mul.dat",true);
        fp("%s %g %g %g\n", Decimal(p).c_str(), rho, dft, mul);
        x << (double)p;
        y << rho;
    }

    std::cerr << "x=" << x << std::endl;
    std::cerr << "y=" << y << std::endl;


    for(size_t i=1;i<y.size();++i)
    {
        if(y[i+1]>=y[i])
        {
            std::cerr << "Keeping " << i << " out of " << y.size() << std::endl;
            x.adjust(i);
            y.adjust(i);
            break;
        }
    }


    Core::HSort::Make(x(), x.size(), Sign::Increasing<double>, y());
    std::cerr << "x=" << x << std::endl;
    std::cerr << "y=" << y << std::endl;
    if(y.head()<0&&y.tail()>0)
    {
        std::cerr << "Looking For Optimal Ratio..." << std::endl;


        ContinuousInterpolation<double,PolynomialInterpolation> F(x,y);
        Triplet<double> xx = { x.head(), 0, x.tail() };
        Triplet<double> yy = { y.head(), 0, y.tail() };
        ZBis<double>   solve;

        const double xopt = solve(F,xx,yy);
        std::cerr << "xopt=" << xopt << std::endl;
    }




}
Y_UDONE()
