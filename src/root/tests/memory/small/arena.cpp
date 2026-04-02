#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/core/rand.hpp"
#include "y/libc/block/zero.h"
#include "y/random/shuffle.hpp"
#include "y/memory/pages.hpp"
#include "y/stream/xmlog.hpp"

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
    Core::Rand            ran;
    Concurrent::Nucleus & nucleus = Concurrent::Nucleus::Instance();
    bool                  verbose = true;
    XML::Log              xml(std::cerr,verbose);

    void *       addr[512];
    const size_t nmax = sizeof(addr)/sizeof(addr[0]);
    size_t       size = 0;

    for(size_t blockSize=1;blockSize<=512;++blockSize)
    {
        std::cerr << "-- blockSize = " << std::setw(4) << blockSize;
        Y_BZero(addr);
        size = 0;
        
        Memory::Small::Arena arena(blockSize,nucleus.book,nucleus.access);
        std::cerr << " | DataAlign = " << std::setw(4) << arena.DataAlign;
        std::cerr << " | numBlocks = " << std::setw(4) << arena.numBlocks;
        std::cerr << " | pageBytes = " << std::setw(8) << arena.allocator.pageBytes;
        std::cerr << " | pageShift = " << std::setw(8) << arena.allocator.pageShift;
        std::cerr << " | lostBytes = " << arena.lostBytesInHeader() << "+" << arena.lostBytesPerChunk();
        std::cerr << std::endl;
        Acquire(nmax,addr,size,arena);

        for(size_t iter=0;iter<16;++iter)
        {
            Random::Shuffle(ran,addr,size);
            Release(size/ran.in<size_t>(2,32),addr,size,arena);
            Acquire(nmax,addr,size,arena);
        }
        Release(0,addr,size,arena);
        //arena.toXML(xml);
    }

    std::cerr << std::endl;
    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxNumBlocks);
    Y_SIZEOF(Memory::Small::Arena);
    Y_SIZEOF(Core::ListOf<Memory::Small::Arena>);

    std::cerr << std::endl;
    for(size_t blockSize=1;blockSize<=512;blockSize<<=1)
    {
        std::cerr << "-- blockSize = " << std::setw(4) << blockSize;
        Memory::Small::Arena arena(blockSize,nucleus.book,nucleus.access);
        std::cerr << " | DataAlign = " << std::setw(4) << arena.DataAlign;
        std::cerr << " | numBlocks = " << std::setw(4) << arena.numBlocks;
        std::cerr << " | pageBytes = " << std::setw(8) << arena.allocator.pageBytes;
        std::cerr << " | pageShift = " << std::setw(8) << arena.allocator.pageShift;
        std::cerr << " | lostBytes = " << arena.lostBytesInHeader() << "+" << arena.lostBytesPerChunk();
        std::cerr << std::endl;
    }





}
Y_UDONE()
