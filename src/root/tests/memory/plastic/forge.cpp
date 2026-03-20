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
            b.size   = ran.in<size_t>(0,1000);
            b.addr = forge.acquire(b.size);
        }
    }


    static inline
    void Release(Memory::Plastic::Forge & forge,
                 const size_t             nmin,
                 Block                    blocks[],
                 size_t                &  size)
    {
        while(size>nmin)
        {
            Block &b = blocks[--size];
            forge.release(b.addr,b.size);
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

    Concurrent::Nucleus &  nucleus = Concurrent::Nucleus::Instance();
    Memory::Plastic::Forge forge(nucleus.book,nucleus.access);

    Block        blocks[10000];
    const size_t nblock = Y_Static_Size(blocks);
    size_t       size   = 0;

    Acquire(forge,nblock,blocks,size,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        Release(forge,nblock/ran.in<size_t>(2,4),blocks,size);
        Acquire(forge,nblock,blocks,size,ran);
    }
    Release(forge,0,blocks,size);


    Y_SIZEOF(Memory::Plastic::Brick);
    Y_SIZEOF(Memory::Plastic::Bricks);
    Y_PRINTV(Memory::Plastic::Forge::DataOffset);
    Y_PRINTV(Memory::Plastic::Forge::MinRawBytes);

    Y_PRINTV(Memory::Plastic::Forge::MinPageBytes);
    Y_PRINTV(Memory::Plastic::Forge::MaxPageBytes);

    Y_PRINTV(Memory::Plastic::Forge::MinPageShift);
    Y_PRINTV(Memory::Plastic::Forge::MaxPageShift);

    Y_SIZEOF(Memory::Plastic::Forge);


}
Y_UDONE()

