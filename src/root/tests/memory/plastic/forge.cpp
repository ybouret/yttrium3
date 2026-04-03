#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;

namespace
{
    struct Block
    {
        void * addr;
        size_t size;
    };

    static inline
    void Acquire(Memory::Plastic::Forge &forge,
                 const size_t            nmax,
                 Block                   blocks[],
                 size_t &                size,
                 Core::Rand &            ran)
    {
        while(size<nmax)
        {
            Block &b = blocks[size++];
            if(ran.choice())
            {
                b.size   = ran.in<size_t>(0,1000);
                b.addr   = forge.acquire(b.size);
            }
            else
            {
                b.size = 0;
                b.addr = forge.legacyAcquire(ran.in<size_t>(0,1000));
            }
        }
    }


    static inline
    void Release(Memory::Plastic::Forge & forge,
                 const size_t             nmin,
                 Block                    blocks[],
                 size_t                &  size )
    {
        while(size>nmin)
        {
            Block &b = blocks[--size];
            Y_ASSERT(0!=b.addr);
            if(b.size>0)
            {
                forge.release(b.addr,b.size);
            }
            else
            {
                forge.legacyRelease(b.addr);
                b.addr = 0;
            }
        }
    }
}

Y_UTEST(memory_plastic_forge)
{
    Core::Rand ran;


    for(size_t blockSize=0;blockSize<=100000; blockSize += ran.in<size_t>(1,1000))
    {
        const unsigned shift = Memory::Plastic::Forge::ShiftFor(blockSize);
        const size_t   bytes = size_t(1) << shift;
        std::cerr << std::setw(6) << blockSize << " -> " << bytes << std::endl;
    }

    std::cerr << std::endl;
    (std::cerr << "-- Testing I/O" << std::endl).flush();
    Concurrent::Nucleus &  nucleus = Concurrent::Nucleus::Instance();
    {
        Memory::Plastic::Forge forge(nucleus.book,nucleus.access);

        Block        blocks[10000];
        const size_t nblock = Y_Static_Size(blocks);
        size_t       size   = 0;

        Acquire(forge,nblock,blocks,size,ran);
        for(size_t iter=0;iter<32;++iter)
        {
            Release(forge,nblock/ran.in<size_t>(2,32),blocks,size);
            Acquire(forge,nblock,blocks,size,ran);
        }
        Release(forge,0,blocks,size);


        Y_SIZEOF(Memory::Plastic::Brick);
        Y_SIZEOF(Memory::Plastic::Bricks);
        Y_PRINTV(Memory::Plastic::Forge::BrickOffset);
        Y_PRINTV(Memory::Plastic::Forge::MinRawBytes);

        Y_PRINTV(Memory::Plastic::Forge::MinPageBytes);
        Y_PRINTV(Memory::Plastic::Forge::MaxPageBytes);

        Y_PRINTV(Memory::Plastic::Forge::MinPageShift);
        Y_PRINTV(Memory::Plastic::Forge::MaxPageShift);
        Y_PRINTV(Memory::Plastic::Forge::ReservedSize);


        Y_SIZEOF(Memory::Plastic::Forge);
    }

    std::cerr << std::endl;

    std::cerr << "-- Final checks..." << std::endl;
    {
        Memory::Plastic::Forge forge(nucleus.book,nucleus.access);

        { size_t n=0; void * p = forge.acquire(n); forge.release(p,n); }
        const Memory::Plastic::Bricks * const head = forge->head;
        Y_ASSERT(head!=0);
        Y_PRINTV(head->maxBlockSize);
        const size_t DefaultMaxBlockSize = Memory::Plastic::Forge::DefaultMaxBlockSize;
        Y_CHECK(DefaultMaxBlockSize==head->maxBlockSize);



    }

    {
        Memory::Plastic::Forge forge(nucleus.book,nucleus.access);
        const size_t nmax = 16384 - Memory::Plastic::ForgeMetrics::ReservedSize;
        { size_t n = nmax; void * p = forge.acquire(n); forge.release(p,n); }
        const Memory::Plastic::Bricks * const head = forge->head;
        Y_ASSERT(head!=0);
        Y_PRINTV(head->maxBlockSize);
        Y_PRINTV(nmax);
        Y_CHECK(nmax==head->maxBlockSize);

    }


}
Y_UDONE()

