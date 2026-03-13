#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"
#include "y/calculus/meta2.hpp"


using namespace Yttrium;



Y_UTEST(memory_small_arena)
{


    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSizeLog2);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSize);




    for(size_t blockSize=1;blockSize<=100;++blockSize)
    {
        std::cerr << "-- blockSize = " << std::setw(4) << blockSize;
        Memory::Small::Arena arena(blockSize);
        std::cerr << " | dataAlign = " << std::setw(4) << arena.dataAlign;
        std::cerr << " | numBlocks = " << std::setw(4) << arena.numBlocks;
        std::cerr << " | pageBytes = " << std::setw(8) << arena.pageBytes;
        std::cerr << " | lostBytes = " << arena.lostBytes();
        std::cerr << std::endl;
    }

    
    

}
Y_UDONE()
