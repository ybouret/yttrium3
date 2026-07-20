#include "y/ink/pixmap.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"

using namespace Yttrium;



Y_UTEST(pixmap)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    Ink::Broker seq(seqEngine);
    Ink::Broker par(parEngine);

    Ink::Pixmap<short>  wpxm(32,16);
    Ink::Pixmap<String> spxm(6,4);
    Ink::Pixmap<int>    apxm(seq,CopyOf,wpxm);
    Ink::Pixmap<int>    bpxm(par,CopyOf,wpxm);


}
Y_UDONE()
