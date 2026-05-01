
#include "y/apex/k/dft.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/pointer/auto.hpp"
#include "y/apex/k/mul.hpp"
#include "y/apex/k/cmp.hpp"
#include "y/format/human-readable.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{

    const size_t minBits = 128;
    const size_t maxBits = 4096;

    template <typename WORD, typename CORE>
    static inline
    void testDFT(Core::Rand &ran)
    {

        std::cerr << "-- WORD = " << ( sizeof(WORD) * 8) << " bits | CORE =" << ( sizeof(CORE) * 8) << " bits" << std::endl;
        System::WallTime chrono;
        uint64_t mul64 = 0;
        uint64_t dft64 = 0;

        for(size_t lbits=minBits;lbits<=maxBits;lbits <<=1)
        {
            //std::cerr << lbits << std::endl;
            for(size_t rbits=lbits;rbits<=maxBits;rbits <<=1)
            {
                (std::cerr << " " <<  std::setw(4) << lbits<< " x " << std::setw(4) << rbits).flush();
                KegDFT::Trace = 0;
                KegMul::Trace = 0;
                mul64 = 0;
                dft64 = 0;
                size_t nops = 0;
                do
                {
                    ++nops;
                    AutoPtr< Keg<WORD> > lhs = Keg<WORD>::MakeRandom(ran, lbits );
                    AutoPtr< Keg<WORD> > rhs = Keg<WORD>::MakeRandom(ran, rbits );

                    uint64_t mark = System::WallTime::Ticks();
                    AutoPtr< Keg<WORD> > mul = KegMul::Compute<WORD,CORE>(lhs->word,lhs->words,rhs->word,rhs->words);
                    mul64 += System::WallTime::Ticks() - mark;

                    mark = System::WallTime::Ticks();
                    AutoPtr< Keg<WORD> > dft = KegDFT::Compute(*lhs,*rhs);
                    dft64 += System::WallTime::Ticks() - mark;

                    Y_ASSERT( __Zero__ == KegCmp::ResultFor(*mul,*dft) );
                }
                while( chrono(mul64) < 0.1L );

                const long double cycles = (long double)nops;
                if(KegDFT::Trace&&KegMul::Trace)
                {
                    const long double mulRate = cycles / chrono(KegMul::Trace);
                    const long double dftRate = cycles / chrono(KegDFT::Trace);
                    std::cerr << " |[in]  mul: " <<  HumanReadable(mulRate)  << " dft: " <<  HumanReadable(dftRate);
                    if(dftRate>=mulRate) std::cerr << " (+)"; else std::cerr << " (-)";
                }
                {
                    const long double mulRate = cycles / chrono(mul64);
                    const long double dftRate = cycles / chrono(dft64);
                    std::cerr << " |[out]  mul: " <<  HumanReadable(mulRate)  << " dft: " <<  HumanReadable(dftRate);
                    if(dftRate>=mulRate) std::cerr << " (+)"; else std::cerr << " (-)";
                }
                //std::cerr << "  | mul: " <<  HumanReadable(KegMul::Trace)  << " dft: " <<  HumanReadable(KegDFT::Trace);
                //std::cerr << "| | mul: " <<  HumanReadable(mul64)          << " dft: " <<  HumanReadable(dft64);
                std::cerr << " |";
                (std::cerr << std::endl).flush();
            }
        }

#if 0
        KegDFT::Trace = 0;
        KegMul::Trace = 0;

        for(size_t iter=0;iter<1024;++iter)
        {
            AutoPtr< Keg<WORD> > lhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,200) );
            AutoPtr< Keg<WORD> > rhs = Keg<WORD>::MakeRandom(ran, ran.in<size_t>(0,200) );
            AutoPtr< Keg<WORD> > mul = KegMul::Compute<WORD,CORE>(lhs->word,lhs->words,rhs->word,rhs->words);


           // std::cerr << "lhs=" << lhs->toHex() << std::endl;
           // std::cerr << "rhs=" << rhs->toHex() << std::endl;
            //std::cerr << "mul=" << mul->toHex() << std::endl;

            AutoPtr< Keg<WORD> > dft = KegDFT::Compute(*lhs,*rhs);
            //std::cerr << "dft=" << dft->toHex() << std::endl;
            Y_ASSERT( __Zero__ == KegCmp::ResultFor(*mul,*dft) );
        }

        std::cerr << "Trace = " << KegDFT:: Trace << "/" << KegMul::Trace << std::endl;
#endif
        std::cerr << std::endl;
    }

}

Y_UTEST(apex_k_dft)
{
    Core::Rand ran;
    testDFT<uint8_t,uint16_t>(ran);
    testDFT<uint8_t,uint32_t>(ran);
    testDFT<uint8_t,uint64_t>(ran);

    testDFT<uint16_t,uint32_t>(ran);
    testDFT<uint16_t,uint64_t>(ran);

    testDFT<uint32_t,uint64_t>(ran);

}
Y_UDONE()

