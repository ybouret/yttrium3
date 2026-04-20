#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;

Y_UTEST(container_cxx_series)
{
    Core::Rand     ran;
    CxxSeries<apz> ics(10);

    for(int i=0;i<10;++i)
    {
        if(ran.heads()) ics.pushTail(i); else ics.pushHead(i);
        std::cerr << ics << std::endl;
    }

    Random::Shuffle(ran, ics(), ics.size() );
    std::cerr << ics << std::endl;

    while( ics.size() > 0 )
    {
        if(ran.heads()) ics.popHead(); else ics.popTail();
        std::cerr << ics << std::endl;
    }

}
Y_UDONE()


