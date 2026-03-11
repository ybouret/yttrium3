#include "y/random/fill.hpp"
#include "y/memory/small/chunk.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/libc/zeroed.h"
#include <ctime>

using namespace Yttrium;

Y_UTEST(memory_small_chunk)
{
    Core::Rand ran( (long) time(NULL) );

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
            while(chunk.stillAvailable)
            {
                void * const p = chunk.acquire(blockSize);
                Y_ASSERT( Yttrium_Zeroed(p,blockSize) );
                Random::FillWith(ran,p,blockSize);
            }
        }
    }

}
Y_UDONE()


