#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(memory_plastic_forge)
{
    Core::Rand ran;


    for(size_t blockSize=0;blockSize<=100000; blockSize += ran.in<size_t>(1,1000))
    {
        const unsigned shift = Memory::Plastic::Forge::ShiftFor(blockSize);
        const size_t   bytes = size_t(1) << shift;
        std::cerr << std::setw(6) << blockSize << " -> " << bytes << std::endl;
    }

    Concurrent::Nucleus &  nucleus = Concurrent::Nucleus::Instance();
    Memory::Plastic::Forge forge(nucleus.book,nucleus.access);

#if 0
    for(unsigned shift=Memory::Plastic::Forge::MinPageShift;shift <= 16;++shift)
    {
        Memory::Plastic::Bricks * bricks = forge.newBricks(shift);
        Y_ASSERT(bricks->info==shift);
        std::cerr << ( size_t(1) << shift ) << " => " << bricks->maxBlockSize << std::endl;
    }
#endif


    Y_SIZEOF(Memory::Plastic::Brick);
    Y_SIZEOF(Memory::Plastic::Bricks);
    Y_PRINTV(Memory::Plastic::Forge::DataOffset);
    Y_PRINTV(Memory::Plastic::Forge::MinRawBytes);

    Y_PRINTV(Memory::Plastic::Forge::MinPageBytes);
    Y_PRINTV(Memory::Plastic::Forge::MaxPageBytes);

    Y_PRINTV(Memory::Plastic::Forge::MinPageShift);
    Y_PRINTV(Memory::Plastic::Forge::MaxPageShift);
}
Y_UDONE()

