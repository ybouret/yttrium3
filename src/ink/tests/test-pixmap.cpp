#include "y/ink/pixmap.hpp"
#include "y/ink/ops/convert.hpp"
#include "y/ink/ops/get-max.hpp"

#include "y/utest/run.hpp"

#include "y/string.hpp"

#include "y/core/rand.hpp"

using namespace Yttrium;



Y_UTEST(pixmap)
{
    Core::Rand  ran;
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    Ink::Broker seq(seqEngine);
    Ink::Broker par(parEngine);

    Ink::Pixmap<short>  wpxm(16,8);
    for(unit_t y=0;y<wpxm.h;++y)
        for(unit_t x=0;x<wpxm.w;++x)
            wpxm[y][x] = ran.in<short>(0,10000);

    Ink::Pixmap<String> spxm(6,4);
    Ink::Pixmap<int>    apxm(seq,CopyOf,wpxm);
    Ink::Pixmap<int>    bpxm(par,CopyOf,wpxm);


    const short wmaxSeq = Ink::Ops::GetMax(seq,wpxm);
    const short wmaxPar = Ink::Ops::GetMax(seq,wpxm);

    Y_PRINTV(wmaxSeq);
    Y_PRINTV(wmaxPar);
    Y_CHECK(wmaxSeq==wmaxPar);
    



}
Y_UDONE()
