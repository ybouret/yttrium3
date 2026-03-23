#include "y/memory/allocator/global.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_allocator)
{
    Concurrent::Singulet::Verbose = true;

    Memory::Global &G = Memory::Global::Instance();

    std::cerr << G.callSign() << "@" << G.lifeTime() << std::endl;
}
Y_UDONE()

