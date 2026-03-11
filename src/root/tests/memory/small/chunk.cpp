#include "y/memory/small/chunk.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_small_chunk)
{
    Y_SIZEOF(Memory::Small::Chunk);

    char data[2048];
    const size_t maxBlockSize = sizeof(data)/255;
    std::cerr << "maxBlockSize=" << maxBlockSize << std::endl;
    for(size_t blockSize=1;blockSize<=maxBlockSize;++blockSize)
    {
        std::cerr << "-- blockSize=" << blockSize << std::endl;
        for(uint8_t numBlocks=1;numBlocks;++numBlocks)
        {
            Memory::Small::Chunk chunk(blockSize,numBlocks,data);
        }
    }

    //Y_ASSERT(NULL==data);
}
Y_UDONE()


