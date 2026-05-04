#include "y/apex/k/dft.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/format/human-readable.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;
using namespace Apex;

static size_t      minBits = 64;
static size_t      maxBits = 512;
static long double tmx     = 0.01L;

template <typename WORD> static inline
void testDFT(Core::Rand &ran)
{
    System::WallTime chrono;
    for(size_t lbits=minBits;lbits<=maxBits;lbits <<=1)
    {
        for(size_t rbits=lbits;rbits<=lbits;rbits <<=1)
        {
            (std::cerr << " " <<  std::setw(4) << lbits<< " x " << std::setw(4) << rbits).flush();
            KegDFT::Trace   = 0;
            uint64_t dft64  = 0;
            size_t   nops   = 0;
            do {
                ++nops;
                AutoPtr< Keg<WORD> > lhs = Keg<WORD>::MakeRandom(ran, lbits );
                AutoPtr< Keg<WORD> > rhs = Keg<WORD>::MakeRandom(ran, rbits );

                const uint64_t mark = System::WallTime::Ticks();
                AutoPtr< Keg<WORD> > dft = KegDFT::Compute(*lhs,*rhs);
                dft64 += System::WallTime::Ticks() - mark;
            }
            while( chrono(dft64) < tmx );
            const long double cycles = (const long double)nops;
            {
                const long double rate = cycles / chrono(dft64);
                std::cerr << " | " << HumanReadable(rate);
            }

            std::cerr << std::endl;
        }
    }
}




Y_UTEST(apex_perf)
{
    Core::Rand ran;
    if(argc>1) tmx = ASCII::Convert::To<long double>(argv[1],"tmx",0);
    testDFT<uint8_t>(ran);
}
Y_UDONE()
