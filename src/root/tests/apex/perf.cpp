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

using namespace Yttrium;
using namespace Apex;

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
#if 0
    Core::Rand ran;
    if (argc > 1) tmx = ASCII::Convert::To<long double>(argv[1], "tmx", 0);

    if (0)
    {
        TestDFT<uint8_t, uint16_t>();
        TestDFT<uint8_t, uint32_t>();
        TestDFT<uint8_t, uint64_t>();
        TestDFT<uint16_t, uint32_t>();
        TestDFT<uint16_t, uint64_t>();
    }
    TestDFT<uint32_t, uint64_t>();
#else
    //size_t bits = 8;
    //if (argc > 1) bits = ASCII::Convert::To<size_t>(argv[1], "bits", 0);
    //Y_PRINTV(bits);
    //CompareDFT<uint32_t, uint64_t>(bits);

    OutputFile::Overwrite("apex-mul.dat");
    static const size_t one=1;
    for(unsigned p=6;p<=16;++p)
    {
        const size_t bits=one<<p;
        double dft=0,mul=0;
        const double rho = CompareDFT<uint32_t,uint64_t>(dft,mul,bits);
        OutputFile     fp("apex-mul.dat",true);
        fp("%s %g %g %g\n", Decimal(p).c_str(), std::log(rho), dft, mul);
    }

    //for (size_t i = 1; i <= bits; ++i) CompareDFT<uint32_t, uint64_t>(i);
#endif

}
Y_UDONE()
