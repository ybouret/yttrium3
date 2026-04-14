#include "y/memory/buffer/static.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_buffer)
{

    Memory::StaticBuffer<16> buff;

    std::cerr << buff << std::endl;

}
Y_UDONE()

