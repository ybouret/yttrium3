#include "y/memory/allocator/global.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/allocator/archon.hpp"

#include "y/memory/small/blocks.hpp"
#include "y/core/rand.hpp"
#include "y/libc/block/zeroed.h"
#include "y/random/fill.hpp"
#include "y/random/shuffle.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

namespace
{
    struct Block
    {
        void * addr;
        size_t size;
    };

    static inline
    void Acquire(Memory::Allocator & alloc,
                 const size_t        nmax,
                 Block               blocks[],
                 size_t       &      count,
                 Core::Rand   &      ran)
    {
        while(count<nmax)
        {
            Block & b = blocks[count];
            b.size    = ran.in<size_t>(0,4000);
            b.addr    = alloc.acquire(b.size);
            Y_ASSERT( Y_TRUE == Yttrium_Zeroed(b.addr,b.size) );
            Random::FillWith(ran,b.addr,b.size,1);
            ++count;
        }
    }

    static inline
    void Release(Memory::Allocator & alloc,
                 const size_t        nmin,
                 Block               blocks[],
                 size_t &            count) noexcept
    {
        while(count>nmin)
        {
            Block & b = blocks[--count];
            alloc.release(b.addr,b.size);
        }
    }

    template <typename ALLOCATOR>
    static inline
    void Perform(ALLOCATOR &alloc, Core::Rand &ran)
    {
        std::cerr << "Perform with " << alloc.callSign() << std::endl;
        Block        blocks[512];
        const size_t nblock = Y_Static_Size(blocks);
        size_t       count  = 0;

        Acquire(alloc,nblock,blocks,count,ran);
        for(size_t iter=0;iter<128;++iter)
        {
            Random::Shuffle(ran,blocks,count);
            Release(alloc,count/ran.in<size_t>(2,16), blocks,count);
            Acquire(alloc,nblock,blocks,count,ran);
        }
        Release(alloc,0,blocks,count);

    }
}

Y_UTEST(memory_allocator)
{
    Concurrent::Singulet::Verbose = true;
    Core::Rand ran;

    Memory::Dyadic &D = Memory::Dyadic::Instance();
    Memory::Global &G = Memory::Global::Instance();
    Memory::Pooled &P = Memory::Pooled::Instance();
    Memory::Archon &A = Memory::Archon::Instance();


    Perform(G,ran);
    Perform(P,ran);
    Perform(D,ran);
    Perform(A,ran);





}
Y_UDONE()

