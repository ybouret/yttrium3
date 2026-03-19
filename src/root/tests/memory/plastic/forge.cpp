#include "y/memory/plastic/forge.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_plastic_forge)
{
    Y_SIZEOF(Memory::Plastic::Brick);
    Y_SIZEOF(Memory::Plastic::Bricks);
    Y_PRINTV(Memory::Plastic::Forge::DataOffset);
    Y_PRINTV(Memory::Plastic::Forge::MinRawBytes);

}
Y_UDONE()

