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

using namespace Yttrium;
using namespace Apex;

namespace
{

    static inline
    double average(const Vector<uint64_t>& arr,
                   double&                 err,
                   const apn   &           sum)
    {
        err = 0;
        const size_t num = arr.size();
        const apq ave(sum, num);
        if (num > 0)
        {
            apq err2;
            for (size_t i = num; i > 0; --i)
            {
                const apn _ = arr[i];
                const apq del = ave - _;
                err2 += del * del;
            }
            const apn den = num * num;
            err2 /= den;
            err = std::sqrt(err2.ratio<double>());
        }
        return ave.ratio<double>();
    }

    static const size_t WarmUp  = 100;
    static double       RhoMax  = 0.05L;
    static const size_t Storage = 1024 * 1024;


    template <typename WORD, typename CORE> static inline
    void CompareDFT(double &dftScore, double &mulScore, const size_t nbits)
    {
        typedef Keg<WORD> KegType;
        (std::cerr << "\tDFT(" << std::setw(4) << nbits << " bits) -- " << sizeof(WORD) * 8 << "-bits | " << sizeof(CORE) * 8 << "-bits: " << std::endl).flush();

        Core::Rand       ran;
        System::WallTime chrono;
        Vector<uint64_t> dft64(WithAtLeast, Storage);
        Vector<uint64_t> mul64(WithAtLeast, Storage);
        apn dftSum;
        apn mulSum;
        while (true)
        {
            const AutoPtr< KegType > lhs = KegType::MakeRandom(ran, nbits);  assert(lhs.isValid()); assert(nbits == lhs->bits);
            const AutoPtr< KegType > rhs = KegType::MakeRandom(ran, nbits);  assert(rhs.isValid()); assert(nbits == rhs->bits);

            // gather timings
            uint64_t                 m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > dft = KegDFT::Compute(*lhs, *rhs);
            {
                const uint64_t ell = System::WallTime::Ticks() - m64;
                dft64 << ell;
                dftSum += ell;
            }

            m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > mul = KegMul::Compute<WORD, CORE>(lhs->word, lhs->words, rhs->word, rhs->words);
            {
                const uint64_t ell = System::WallTime::Ticks() - m64;
                mul64 << ell;
                mulSum += ell;
            }

            //Y_ASSERT( __Zero__ == KegCmp::ResultFor(*mul,*dft) );


            // compute average sign and standard error
            double       dftErr = 0;
            double       mulErr = 0;
            const double dftAve = average(dft64, dftErr, dftSum);
            const double mulAve = average(mul64, mulErr, mulSum);
            const double dftRho = dftErr / dftAve;
            const double mulRho = mulErr / mulAve;

#if 0
            std::cerr
            << "<dft> = " << dftAve << " +/- " << dftErr << " @" << dftRho
            << " | "
            << "<mul> = " << mulAve << " +/- " << mulErr << " @" << mulRho
            << std::endl;
#endif

            const size_t card = dft64.size();

            if (card < WarmUp)
                continue;

            if (dftRho < RhoMax && mulRho < RhoMax)
            {
                dftScore = dftAve;
                mulScore = mulAve;
                return;
            }

        };

    }

    static const size_t MaxOps = 30;

    template <typename WORD, typename CORE> static inline
    void TestDFT()
    {
        (std::cerr << "-- DFT [MUL]" << std::setw(3) << sizeof(WORD) * 8 << "-bits | " << std::setw(3) << sizeof(CORE) * 8 << "-bits: ").flush();
        size_t   lowerBits = 8;
        SignType lowerSign = CompareDFT<WORD, CORE>(lowerBits); Y_ASSERT(lowerSign == Positive);
        size_t   upperBits = lowerBits;
        size_t   count = 0;
        std::cerr << "[";
        do
        {
            upperBits <<= 1;
            ++count; (std::cerr << '#').flush();
        } while (Negative != CompareDFT<WORD, CORE>(upperBits));

        while (upperBits - lowerBits > 1)
        {
            ++count;
            const size_t   middleBits = (upperBits + lowerBits) >> 1;
            const SignType middleSign = CompareDFT<WORD, CORE>(middleBits);
            switch (middleSign)
            {
                case Positive:  (std::cerr << '+').flush(); lowerBits = middleBits; continue;
                case Negative:  (std::cerr << '-').flush(); upperBits = middleBits; continue;
                case __Zero__:  (std::cerr << '*').flush(); upperBits = lowerBits = middleBits;
                    break;
            }
            break;
        }
        const size_t upperBytes = Alignment::On<8>::Ceil(upperBits) / 8;
        std::cerr << "]";
        while (++count < MaxOps) std::cerr << ' ';
        std::cerr << "==> " << std::setw(5) << upperBits << " bits | " << std::setw(5) << upperBytes << " bytes" << std::endl;

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
    for(unsigned bits=1000;bits<=24000;bits += 500)
    {
        double dft=0,mul=0;
        CompareDFT<uint32_t,uint64_t>(dft,mul,bits);
        OutputFile     fp("apex-mul.dat",true);
        fp("%u %g %g\n", bits, dft, mul);
    }

    //for (size_t i = 1; i <= bits; ++i) CompareDFT<uint32_t, uint64_t>(i);
#endif

}
Y_UDONE()
