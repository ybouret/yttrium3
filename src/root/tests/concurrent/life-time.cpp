#include "y/concurrent/life-time.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

#define Y_Show_LifeTimeFor(NAME) Y_PRINTV(LifeTimeFor::NAME)

Y_UTEST(concurrent_life_time)
{
    Y_Show_LifeTimeFor(ConcurrentNucleus);
    Y_Show_LifeTimeFor(MemoryGlobal);
    Y_Show_LifeTimeFor(MemoryPooled);
    Y_Show_LifeTimeFor(MemoryDyadic);
    Y_Show_LifeTimeFor(MemoryArchon);
    Y_Show_LifeTimeFor(ObjectFactory);

}
Y_UDONE()
