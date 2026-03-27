
#include "y/memory/allocator/archon.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"
#include "y/random/fill.hpp"
#include "y/libc/block/zeroed.h"

#include "y/utest/run.hpp"


using namespace Yttrium;

namespace {

    struct Block
    {
        void * addr;
        size_t size;
    };

    static inline
    void Acquire(Memory::Archon & archon,
                 const size_t     nmax,
                 Block            blocks[],
                 size_t       &   count,
                 Core::Rand   &   ran)
    {
        while(count<nmax)
        {
            Block & b = blocks[count];
            b.size    = ran.in<size_t>(0,4000);
            b.addr    = archon.acquire(b.size);
            Y_ASSERT( Y_TRUE == Yttrium_Zeroed(b.addr,b.size) );
            Random::FillWith(ran,b.addr,b.size,1);
            ++count;
        }
    }


    static inline
    void Release(Memory::Archon & archon,
                 const size_t     nmin,
                 Block            blocks[],
                 size_t          &count) noexcept
    {
        while(count>nmin)
        {
            Block & b = blocks[--count];
            archon.release(b.addr,b.size);
        }
    }

}

Y_UTEST(memory_archon)
{
    Concurrent::Singulet::Verbose = true;
    Core::Rand ran;
    Y_PRINTV(Memory::Archon::MinBlockBytes);
    Y_PRINTV(Memory::Archon::MaxBlockBytes);
    Y_PRINTV(Memory::Archon::MinBlockShift);
    Y_PRINTV(Memory::Archon::MaxBlockShift);

    Memory::Archon &archon = Memory::Archon::Instance();
    std::cerr << "Using " << archon.callSign() << std::endl;

    Block        blocks[100];
    const size_t nblock = Y_Static_Size(blocks);
    size_t       count  = 0;

    Acquire(archon,nblock,blocks,count,ran);
    {
        Random::Shuffle(ran,blocks,count);
        Release(archon,count/ran.in<size_t>(2,4), blocks,count);
        Acquire(archon,nblock,blocks,count,ran);
    }
    Release(archon,0,blocks,count);

    

    archon.writeXML(std::cerr);
    archon.gc(128);
    archon.writeXML(std::cerr);


}
Y_UDONE()

