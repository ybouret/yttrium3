#include "y/memory/small/blocks.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/nucleus.hpp"
#include "y/core/rand.hpp"

#include "y/stream/xmlog.hpp"

using namespace Yttrium;

namespace
{
    struct Blk
    {
        void * addr;
        size_t size;
    };

    static void Acquire(Memory::Small::Blocks &B, const size_t ntop, Blk blks[], size_t &size, Core::Rand &ran)
    {
        while(size<ntop)
        {
            Blk &b = blks[size++];
            b.size = ran.in<size_t>(1,300);
            b.addr = B.acquire(b.size);
        }
    }

    static void Release(Memory::Small::Blocks &B, const size_t nmin, Blk blks[], size_t &size)
    {
        while(size>nmin)
        {
            Blk &b = blks[--size];
            B.release(b.addr,b.size);
        }
    }

    static void Check(const Memory::Small::Blocks &B, const Blk blks[], const size_t size)
    {
        for(size_t i=0;i<size;++i)
        {
            const Blk &b = blks[i];
            size_t     bs = 0;
            Y_ASSERT(B.owns(b.addr,bs));
            Y_ASSERT(bs==b.size);
        }
    }

}

Y_UTEST(memory_small_blocks)
{
    Core::Rand            ran;
    Concurrent::Nucleus & nucleus = Concurrent::Nucleus::Instance();

    Memory::Small::Blocks blocks(nucleus.book,nucleus.access);


    Y_PRINTV(Memory::Small::Blocks::BytesPerSlot);
    Y_PRINTV(Memory::Small::Blocks::DefaultBytes);
    Y_PRINTV(Memory::Small::Blocks::TableSize);
    Y_PRINTV(Memory::Small::Blocks::TableMask);
    Y_PRINTV(Memory::Small::Blocks::TableBytes);
    Y_PRINTV(Memory::Small::Blocks::TableWords);

    Blk          blks[1000];
    const size_t nmax = Y_Static_Size(blks);
    size_t       size = 0;

    Acquire(blocks,nmax,blks,size,ran);

    for(size_t iter=0;iter<10;++iter)
    {
        Check(blocks,blks,size);
        Release(blocks,size/ran.in<size_t>(2,4),blks,size);
        Acquire(blocks,nmax,blks,size,ran);
    }

    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);
    blocks.toXML(xml);
    Release(blocks,0,blks,size);

}
Y_UDONE()
