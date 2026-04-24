
#include "y/memory/buffer/classified.hpp"
#include "y/memory/buffer/allocated.hpp"
#include "y/memory/buffer/static.hpp"
#include "y/utest/run.hpp"

#include "y/memory/allocator/archon.hpp"
#include "y/memory/allocator/global.hpp"
#include "y/memory/allocator/pooled.hpp"

using namespace Yttrium;

Y_UTEST(memory_buffer)
{

    Memory::StaticBuffer<16> buff;

    std::cerr << "buff=" << buff << std::endl;

    Memory::AllocatedBuffer<Memory::Global> gbuf(0);
    std::cerr << "gbuf=" << gbuf << std::endl;

    Memory::AllocatedBuffer<Memory::Pooled> pbuf(0);
    std::cerr << "pbuf=" << pbuf << std::endl;

    Memory::AllocatedBuffer<Memory::Archon> abuf(0);
    std::cerr << "abuf=" << abuf << std::endl;

    Memory::Classified<uint64_t,Memory::Pooled> cls(10);
    

}
Y_UDONE()

