
#include "y/apex/k/dft.hpp"
#include "y/apex/k/mul.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/format/human-readable.hpp"
#include "y/ascii/convert.hpp"
#include "y/system/wall-time.hpp"

#include "y/format/percent.hpp"

using namespace Yttrium;
using namespace Apex;


static long double tmx     = 0.01L;

template <typename WORD, typename CORE> static inline
SignType CompareDFT(const size_t nbits)
{
    //(std::cerr << "\tDFT(" << std::setw(4) << nbits << ") -- " << sizeof(WORD)*8 << "-bits | " << sizeof(CORE)*8 << "-bits: ").flush();

    Core::Rand       ran;
    System::WallTime chrono;

    uint64_t dft64  = 0;
    uint64_t mul64  = 0;
    SignType last   = __Zero__;
    size_t   same   = 0;
    do {
        //++nops;
        AutoPtr< Keg<WORD> > lhs  = Keg<WORD>::MakeRandom(ran, nbits);

        uint64_t             mark = System::WallTime::Ticks();
        AutoPtr< Keg<WORD> > dft  = KegDFT::Square(*lhs);
        dft64 += System::WallTime::Ticks() - mark;

        mark = System::WallTime::Ticks();
        AutoPtr< Keg<WORD> > mul  = KegMul::Square<WORD,CORE>(lhs->word, lhs->words);
        mul64 += System::WallTime::Ticks() - mark;

        const SignType curr = Sign::Of(dft64,mul64);
        if(curr==last)
        {
            ++same;
        }
        else
        {
            last = curr;
            same = 1;
        }
        //std::cerr << "same=" << same << std::endl;
    }
    while( chrono(dft64) < tmx || same < 10);
    //std::cerr << nbits << "\t=> " << std::setw(3) << last << " #same=" << std::setw(8) << same << std::endl;
    return last;
}

static const size_t MaxOps = 30;

template <typename WORD, typename CORE> static inline
void TestDFT()
{
    (std::cerr << "-- DFT [SQR] " << std::setw(3) << sizeof(WORD)*8 << "-bits | " << std::setw(3) << sizeof(CORE)*8 << "-bits: ").flush();
    size_t   lowerBits = 8;
    SignType lowerSign = CompareDFT<WORD,CORE>(lowerBits); Y_ASSERT(lowerSign == Positive);
    size_t   upperBits = lowerBits;
    size_t   count     = 0;
    std::cerr << "[";
    do
    {
        upperBits <<= 1;
        ++count; (std::cerr << '.').flush();
    } while( Negative !=  CompareDFT<WORD,CORE>(upperBits) );

    while(upperBits-lowerBits>1)
    {
        ++count; (std::cerr << '.').flush();
        const size_t   middleBits = (upperBits+lowerBits) >> 1;
        const SignType middleSign = CompareDFT<WORD,CORE>(middleBits);
        switch(middleSign)
        {
            case Positive: lowerBits = middleBits; continue;
            case Negative: upperBits = middleBits; continue;
            case __Zero__: upperBits = lowerBits = middleBits;
                break;
        }
        break;
    }
    const size_t upperBytes = Alignment::On<8>::Ceil(upperBits) / 8;
    std::cerr << "]";
    while(++count<MaxOps) std::cerr << ' ';
    std::cerr << "==> " << std::setw(5) << upperBits << " bits | " << std::setw(5) << upperBytes << " bytes" << std::endl;

}




Y_UTEST(apex_perf2)
{
    Core::Rand ran;
    if(argc>1) tmx = ASCII::Convert::To<long double>(argv[1],"tmx",0);

#if 0
    TestDFT<uint8_t,uint16_t>();
    TestDFT<uint8_t,uint32_t>();
    TestDFT<uint8_t,uint64_t>();
    TestDFT<uint16_t,uint32_t>();
    TestDFT<uint16_t,uint64_t>();
#endif

    TestDFT<uint32_t,uint64_t>();

    

}
Y_UDONE()
