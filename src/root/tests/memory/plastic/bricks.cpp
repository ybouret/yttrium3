#include "y/memory/plastic/bricks.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
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


    void * data[100];
    Memory::Plastic::Bricks bricks(data,sizeof(data));
    
    Y_PRINTV(sizeof(data));
    Y_CHECK(bricks.areEmpty());
    Y_PRINTV(bricks.head->size);

    Block   blocks[1024];
    size_t  nblock = 0;

    Acquire(bricks,blocks,nblock,ran);



}
Y_UDONE()

