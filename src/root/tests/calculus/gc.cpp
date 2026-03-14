#include "y/calculus/gc.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"




using namespace Yttrium;



Y_UTEST(calculus_gc)
{

    Core::Rand ran;

    uint64_t qw = 0;
    for(size_t iter=0;iter<10;++iter)
    {
        Random::FillWord(ran,qw);
        std::cerr << Hexadecimal(qw) << std::endl;
        for(unsigned keep=0;keep<256;++keep)
        {
            const uint64_t kept = Calculus::GC_::Kept(qw,keep);
            Y_ASSERT(kept<=qw);
        }
    }

    for(size_t size=0;size<=1000;size+=1+ran.leq<size_t>(10))
    {
        std::cerr << std::setw(5) << size;
        uint8_t keep = 0;
        while(true)
        {
            const size_t kept = GC::Kept(size,keep);
            std::cerr << "|" << std::setw(4) << (int)keep << ":" << std::setw(5) << kept;
            if(255==keep) break;
        CHOOSE_DELTA:
            size_t delta = ran.leq<size_t>(255-keep);
            if(delta<=0) goto CHOOSE_DELTA;
            keep += delta;
        }
        std::cerr << std::endl;
    }




}
Y_UDONE()

