#include "y/memory/allocator/global.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace Memory
    {
        
    }
}


Y_UTEST(memory_allocator)
{
    Concurrent::Singulet::Verbose = true;

    Memory::Global &G = Memory::Global::Instance();
    Memory::Pooled &P = Memory::Pooled::Instance();

    std::cerr << G.callSign() << "@" << G.lifeTime() << std::endl;
    std::cerr << P.callSign() << "@" << P.lifeTime() << std::endl;

}
Y_UDONE()

