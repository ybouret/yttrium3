
#include "y/memory/allocator/archon.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;



Y_UTEST(memory_archon)
{
    Concurrent::Singulet::Verbose = true;
    
    Y_PRINTV(Memory::Archon::MinBlockBytes);
    Y_PRINTV(Memory::Archon::MaxBlockBytes);
    Y_PRINTV(Memory::Archon::MinBlockShift);
    Y_PRINTV(Memory::Archon::MaxBlockShift);

    Memory::Archon &archon = Memory::Archon::Instance();
    std::cerr << "Using " << archon.callSign() << std::endl;

    unsigned shift = archon.MinBlockShift;
    void *   block = archon.acquireBlock(shift);

    archon.releaseBlock(block,shift);

    archon.writeXML(std::cerr);

}
Y_UDONE()

