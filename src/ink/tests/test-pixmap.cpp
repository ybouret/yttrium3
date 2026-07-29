#include "y/ink/pixmap.hpp"
#include "y/ink/ops/convert.hpp"
#include "y/ink/ops/get-max.hpp"
#include "y/ink/ops/get-min.hpp"
#include "y/ink/ops/min-max.hpp"

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
            wpxm[y][x] = ran.in<short>(0,30000);

    Ink::Pixmap<String> spxm(6,4);
    Ink::Pixmap<int>    apxm(seq,CopyOf,wpxm);
    Ink::Pixmap<int>    bpxm(par,CopyOf,wpxm);


    const short wmaxSeq = Ink::Ops::GetMax(seq,wpxm);
    const short wmaxPar = Ink::Ops::GetMax(par,wpxm);

    Y_PRINTV(wmaxSeq);
    Y_PRINTV(wmaxPar);
    Y_CHECK(wmaxSeq==wmaxPar);
    
    const short wminSeq = Ink::Ops::GetMin(seq,wpxm);
    const short wminPar = Ink::Ops::GetMin(par,wpxm);

    Y_PRINTV(wminSeq);
    Y_PRINTV(wminPar);
    Y_CHECK(wminSeq==wminPar);

    const Ink::Ops::PixelRange<short> rangeSeq = Ink::Ops::MinMax(seq,wpxm);
    const Ink::Ops::PixelRange<short> rangePar = Ink::Ops::MinMax(par,wpxm);
    Y_CHECK(wminSeq==rangeSeq.vmin);
    Y_CHECK(wmaxSeq==rangeSeq.vmax);
    Y_CHECK(wminPar==rangePar.vmin);
    Y_CHECK(wmaxPar==rangePar.vmax);
}
Y_UDONE()
