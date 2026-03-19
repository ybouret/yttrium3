#include "y/memory/plastic/forge.hpp"
#include "y/utest/run.hpp"

#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(memory_plastic_forge)
{
    Core::Rand ran;
    Y_SIZEOF(Memory::Plastic::Brick);
    Y_SIZEOF(Memory::Plastic::Bricks);
    Y_PRINTV(Memory::Plastic::Forge::DataOffset);
    Y_PRINTV(Memory::Plastic::Forge::MinRawBytes);

    for(size_t blockSize=0;blockSize<=100000; blockSize += ran.in<size_t>(1,1000))
    {
        const unsigned shift = Memory::Plastic::Forge::ShiftFor(blockSize);
        const size_t   bytes = size_t(1) << shift;
        std::cerr << std::setw(6) << blockSize << " -> " << bytes << std::endl;
    }



}
Y_UDONE()

