#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/core/rand.hpp"
#include "y/libc/bzero.h"
#include "y/random/shuffle.hpp"

using namespace Yttrium;


namespace
{
    static inline
    void Acquire(const size_t nmax, void * addr[], size_t &size, Memory::Small::Arena &arena)
    {
        while(size<nmax)
            addr[size++] = arena.acquire();

    }

    static inline
    void Release(const size_t nmin, void * addr[], size_t &size, Memory::Small::Arena &arena)
    {
        while(size>nmin)
            arena.release( addr[--size] );
    }
}

Y_UTEST(memory_small_arena)
{
    Core::Rand           ran;
    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    Memory::Book         book(nucleus);


    void *       addr[1000];
    const size_t nmax = sizeof(addr)/sizeof(addr[0]);
    size_t       size = 0;

    for(size_t blockSize=1;blockSize<=256;++blockSize)
    {
        std::cerr << "-- blockSize = " << std::setw(4) << blockSize;
        Y_BZero(addr);
        size = 0;
        
        Memory::Small::Arena arena(blockSize,book);
        std::cerr << " | dataAlign = " << std::setw(4) << arena.dataAlign;
        std::cerr << " | numBlocks = " << std::setw(4) << arena.numBlocks;
        std::cerr << " | pageBytes = " << std::setw(8) << arena.allocator.pageBytes;
        std::cerr << " | pageShift = " << std::setw(8) << arena.allocator.pageShift;
        std::cerr << " | lostBytes = " << arena.lostBytesPerChunk();
        std::cerr << std::endl;
        Acquire(nmax,addr,size,arena);

        Random::Shuffle(ran,addr,size);
        Release(size/2,addr,size,arena);

        //Release(0,addr,size,arena);
    }


    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSizeLog2);
    Y_PRINTV(Memory::Small::Arena::MaxBlockSize);
    Y_SIZEOF(Memory::Small::Arena);


}
Y_UDONE()
