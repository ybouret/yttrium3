#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;

Y_UTEST(container_cxx_series)
{
    Core::Rand     ran;
    const int      n = 10;
    CxxSeries<apz> ics(n);

    for(int i=0;i<n;++i)
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

    for(int i=0;i<n;++i)
    {
        if(ran.heads()) ics.pushTail(i); else ics.pushHead(i);
        std::cerr << ics << std::endl;
    }

    while(ics.size())
    {
        const size_t i = ran.in<size_t>(1,ics.size());
        ics.remove(i);
        std::cerr << "remove #" << std::setw(2) << i << " => " << ics << std::endl;
    }

    for(int i=0;i<n;++i)
    {
        if(ran.heads()) ics.pushTail(i); else ics.pushHead(i);
        std::cerr << ics << std::endl;
    }

    for(size_t i=1;i<=ics.size();++i)
    {
        ics.demote(i);
        std::cerr << "demote #" << std::setw(2) << i << " => " << ics << std::endl;
    }

    
}
Y_UDONE()


