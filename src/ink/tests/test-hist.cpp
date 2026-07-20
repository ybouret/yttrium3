
#include "y/ink/histogram/build.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/string.hpp"
#include "y/stream/libc/output.hpp"

#include <cmath>

using namespace Yttrium;


namespace
{
    static inline
    uint8_t f2b(const float f)
    {
        return floorf(255.0f*f+0.5f);
    }
}

Y_UTEST(hist)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    Ink::Broker         seq(seqEngine);
    Ink::Broker         par(parEngine);
    Core::Rand          ran;
    Ink::Pixmap<float>  pxm(32,16);

    for(unit_t y=0;y<pxm.h;++y)
    {
        for(unit_t x=0;x<pxm.w;++x)
        {
            pxm(y)(x) = ran();
        }
    }

    Ink::Histogram Hseq;
    Ink::Histogram Hpar;

    Ink::BuildHistogram::Add(Hseq,seq,pxm,f2b);
    Ink::BuildHistogram::Add(Hpar,par,pxm,f2b);

    std::cerr << "total: " << Hseq.total << " / " << Hpar.total << std::endl;
    Y_CHECK(Hseq.total==Hpar.total);
    Y_CHECK(Hseq==Hpar);
    Y_CHECK(!(Hseq!=Hpar));
    {
        OutputFile fp("hseq.dat");
        Hseq.save(fp);
    }

    {
        OutputFile fp("hpar.dat");
        Hpar.save(fp);
    }


}
Y_UDONE()
