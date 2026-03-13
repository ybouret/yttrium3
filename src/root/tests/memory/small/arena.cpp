#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_small_arena)
{

    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSize);

    for(size_t blockSize=1;blockSize<=10;++blockSize)
    {
        std::cerr << std::endl;
        Memory::Small::Arena arena(blockSize);
        std::cerr << "-- blockSize = " << arena.blockSize << std::endl;
        std::cerr << "   dataAlign = " << arena.dataAlign << std::endl;
    }


}
Y_UDONE()
