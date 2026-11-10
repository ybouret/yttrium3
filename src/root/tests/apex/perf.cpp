#include "y/apex/k/dft.hpp"
#include "y/apex/k/mul.hpp"
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
    static long double tmx = 0.001L;


    template <typename WORD, typename CORE> static inline
    SignType CompareDFT(const size_t nbits)
    {
        typedef Keg<WORD> KegType;
        (std::cerr << "\tDFT(" << std::setw(4) << nbits << " bits) -- " << sizeof(WORD) * 8 << "-bits | " << sizeof(CORE) * 8 << "-bits: " << std::endl).flush();

        Core::Rand       ran;
        System::WallTime chrono;
        apn              ops   = 0;
        apq              sum   = 0;
        uint64_t         dft64 = 0;
        uint64_t         mul64 = 0;
        Vector<SignType> svec;
        do {
            const AutoPtr< KegType > lhs = KegType::MakeRandom(ran, nbits);  assert(lhs.isValid()); assert(nbits == lhs->bits);
            const AutoPtr< KegType > rhs = KegType::MakeRandom(ran, nbits);  assert(rhs.isValid()); assert(nbits == rhs->bits);

            // gather timings
            uint64_t                 m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > dft = KegDFT::Compute(*lhs, *rhs);
            dft64 += System::WallTime::Ticks() - m64;

            m64 = System::WallTime::Ticks();
            const AutoPtr< KegType > mul = KegMul::Compute<WORD, CORE>(lhs->word, lhs->words, rhs->word, rhs->words);
            mul64 += System::WallTime::Ticks() - m64;

            // compute average sign and standard error
            ++ops;
            const SignType last = Sign::Of(mul64,dft64);
            svec << last;
            switch( last )
            {
                case Negative: --sum; break;
                case Positive: ++sum; break;
                case __Zero__:        break;
            }

            const long double ell = chrono(Min(dft64,mul64));


            const apq ave = sum / ops;
            apq       er2 = 0;
            for(size_t i=svec.size();i>0;--i)
            {
                apq s = svec[i];
                s -= ave;
                er2 += s*s;
            }
            er2 /= ops*ops;
            const long double err = er2.ratio<long double>();
            std::cerr << "ave=" << ave << ", err=" << err << " @" << ops << " during " << ell << ", bits=" << nbits << std::endl;

            if(ell>=tmx && err<=0.01L && ops>=100) break;

        } while (true);
        return sum.numer.s;
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
    for(unsigned bits=1000;bits<=32000;bits += 1000)
    {
        const SignType s = CompareDFT<uint32_t,uint64_t>(bits);
        OutputFile     fp("apex-mul.dat",true);
        fp("%u %d\n", bits, (int)s);
    }

    //for (size_t i = 1; i <= bits; ++i) CompareDFT<uint32_t, uint64_t>(i);
#endif

}
Y_UDONE()
