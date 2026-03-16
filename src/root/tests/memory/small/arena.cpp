#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"
#include "y/calculus/meta2.hpp"
#include "y/concurrent/nucleus.hpp"

using namespace Yttrium;



Y_UTEST(memory_small_arena)
{

    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    Memory::Book         book(nucleus);





    for(size_t blockSize=1;blockSize<=256;++blockSize)
    {
        std::cerr << "-- blockSize = " << std::setw(4) << blockSize;
        Memory::Small::Arena arena(blockSize,book);
        std::cerr << " | dataAlign = " << std::setw(4) << arena.dataAlign;
        std::cerr << " | numBlocks = " << std::setw(4) << arena.numBlocks;
        std::cerr << " | pageBytes = " << std::setw(8) << arena.allocator.pageBytes;
        std::cerr << " | pageShift = " << std::setw(8) << arena.allocator.pageShift;
        std::cerr << " | lostBytes = " << arena.lostBytesPerChunk();
        std::cerr << std::endl;
    }


    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSizeLog2);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSize);
    Y_SIZEOF(Memory::Small::Arena);


}
Y_UDONE()
