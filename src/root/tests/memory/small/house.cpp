#include "y/memory/small/house.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/nucleus.hpp"

using namespace Yttrium;

Y_UTEST(memory_small_house)
{
    Core::Rand                   ran;
    Concurrent::Nucleus &        nucleus = Concurrent::Nucleus::Instance();
    Memory::Book        &        book    = nucleus.book;
    Memory::Small::Arena         arena(8,book,nucleus.access);
    Memory::Small::House<double> house(arena);

    double *     addr[1000];
    const size_t size = Y_Static_Size(addr);

    for(size_t i=0;i<size;++i)
    {
        addr[i] = house.produce();
    }
    Random::Shuffle(ran,addr,size);

    for(size_t i=0;i<size;++i)
    {
        house.recycle(addr[i]);
    }


}
Y_UDONE()
