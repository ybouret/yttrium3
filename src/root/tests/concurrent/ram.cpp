#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/libc/bzero.h"

using namespace Yttrium;

namespace
{
    struct Block
    {
        void * addr;
        size_t size;
    };
}
Y_UTEST(concurrent_ram)
{
    Core::Rand  ran;

    Block        block[1000];
    const size_t nmax = sizeof(block)/sizeof(block[0]);
    Y_BZero(block);

    for(size_t i=0;i<nmax;++i)
    {
        block[i].addr = Concurrent::Nucleus::Acquire( block[i].size = ran.leq<size_t>(1000) );
    }

    //return 0;

    Random::Shuffle(ran,block,nmax);
    for(size_t i=0;i<nmax;++i)
    {
        Concurrent::Nucleus::Release(block[i].addr,block[i].size);
    }

    Y_CHECK(0==Concurrent::Nucleus::RAM);


}
Y_UDONE()

