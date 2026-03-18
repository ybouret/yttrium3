#include "y/memory/plastic/bricks.hpp"
#include "y/utest/run.hpp"
#include "y/random/fill.hpp"
#include "y/random/shuffle.hpp"
#include "y/core/rand.hpp"
#include "y/memory/sentinel.hpp"
#include "y/libc/block/zeroed.h"
using namespace Yttrium;


namespace
{
    struct Block
    {
        void  * addr;
        size_t  size;
    };

    static inline
    void Acquire(Memory::Plastic::Bricks &bricks,
                 Block        blocks[],
                 size_t     & nblock,
                 Core::Rand & ran)
    {
        while(true)
        {
            Block & b = blocks[nblock];
            b.size = ran.in<size_t>(0,100);
            void * const p = b.addr = bricks.acquire(b.size);
            if(!p) break;
            ++nblock;

            const Memory::Plastic::Brick * const self = static_cast<Memory::Plastic::Brick *>(p) - 1;
            const Memory::Plastic::Brick * const next = self->next;
            Y_ASSERT(self->used);
            Y_ASSERT(next);
            Y_ASSERT(self->size==b.size);
            Y_ASSERT( Yttrium_Zeroed(b.addr,b.size) );

            const Memory::Sentinel keepSelf("self",self,sizeof(Memory::Plastic::Brick));
            const Memory::Sentinel keepNext("next",next,sizeof(Memory::Plastic::Brick));

            Random::Fill(ran, (uint8_t *)b.addr, b.size);

        }
    }

    static inline
    void Release(const size_t nmin,
                 Block        blocks[],
                 size_t     & nblock,
                 const Memory::Plastic::Bricks * const owner)
    {
        while(nblock>nmin)
        {
            Block &b = blocks[--nblock];
            Y_ASSERT(owner==Memory::Plastic::Bricks::Release(b.addr,b.size));

        }
    }



}

Y_UTEST(memory_plastic_bricks)
{
    Core::Rand ran;

    Y_SIZEOF(Memory::Plastic::Brick);
    Y_PRINTV(Memory::Plastic::Bricks::BrickBytes);
    Y_PRINTV(Memory::Plastic::Bricks::MinPerPage);
    Y_PRINTV(Memory::Plastic::Bricks::MinBlockSize);
    //Y_PRINTV(Memory::Plastic::Bricks::MinPageBytes);
    //Y_PRINTV(Memory::Plastic::Bricks::MinPageShift);


    void * data[500];
    Memory::Plastic::Bricks bricks(data,sizeof(data));
    
    Y_PRINTV(sizeof(data));
    Y_CHECK(bricks.areEmpty());
    Y_PRINTV(bricks.head->size);
    Y_PRINTV(bricks.maxBlockSize);

    Block   blocks[1024];
    size_t  nblock = 0;
    Acquire(bricks,blocks,nblock,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        Random::Shuffle(ran,blocks,nblock);
        Release(nblock / ran.in<size_t>(1,4),blocks,nblock, &bricks);
        Acquire(bricks,blocks,nblock,ran);
    }
    Release(0,blocks,nblock, &bricks);

    Y_CHECK(bricks.areEmpty());
}
Y_UDONE()

