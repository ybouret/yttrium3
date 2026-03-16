#include "y/random/fill.hpp"
#include "y/random/shuffle.hpp"
#include "y/memory/small/chunk.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"
#include "y/libc/block/zeroed.h"
#include <ctime>
#include <cstring>


using namespace Yttrium;

namespace
{
    static inline
    void AcquireUpTo(const size_t n,
                     void * addr[],
                     size_t &nblk,
                     Memory::Small::Chunk &chunk,
                     const size_t blockSize,
                     Core::Rand &ran)
    {
        while(nblk<n)
        {
            void * const p = (addr[nblk++] = chunk.acquire(blockSize));
            Y_ASSERT( Yttrium_Zeroed(p,blockSize) );
            Random::FillWith(ran,p,blockSize);
        }
    }

    static inline
    void ReleaseDown(const size_t n,
                     void * addr[],
                     size_t &nblk,
                     Memory::Small::Chunk &chunk,
                     const size_t blockSize)
    {
        while(nblk>n)
        {
            chunk.release(addr[--nblk],blockSize);
        }
    }
}

Y_UTEST(memory_small_chunk)
{
    Core::Rand ran( (long) time(NULL) );

    Y_SIZEOF(Memory::Small::Chunk);


    void * addr[256];
    size_t nblk = 0;
    char   data[4096];
    const size_t maxBlockSize = sizeof(data)/255;
    std::cerr << "maxBlockSize=" << maxBlockSize << std::endl;
    for(size_t blockSize=1;blockSize<=maxBlockSize;++blockSize)
    {
        std::cerr << "-- blockSize=" << blockSize << std::endl;
        for(uint8_t numBlocks=1;numBlocks;++numBlocks)
        {
            Memory::Small::Chunk chunk(blockSize,numBlocks,data);
            memset(addr,0,sizeof(addr));
            AcquireUpTo(numBlocks,addr,nblk,chunk,blockSize,ran);
            for(size_t iter=0;iter<10;++iter)
            {
                Random::Shuffle(ran,addr,nblk);
                ReleaseDown(nblk>>1,addr,nblk,chunk,blockSize);
            }
            ReleaseDown(0,addr,nblk,chunk,blockSize);
        }
    }

}
Y_UDONE()


