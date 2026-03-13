#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"
#include "y/calculus/meta2.hpp"


using namespace Yttrium;



Y_UTEST(memory_small_arena)
{


    Y_PRINTV(Memory::Small::Arena::MinNumBlocks);
    Y_PRINTV(Memory::Small::Arena::MaxNumBlocks);
    Y_PRINTV(Memory::Small::Arena::ChunkBytes);
    Y_PRINTV(Memory::Small::Arena::ChunkExp2Bytes);
    Y_PRINTV(Memory::Small::Arena::ChunkExp2Shift);


    for(size_t blockSize=1;blockSize<=10;++blockSize)
    {
        std::cerr << std::endl;
        Memory::Small::Arena arena(blockSize);
        std::cerr << "-- blockSize = " << arena.blockSize << std::endl;
        std::cerr << "   dataAlign = " << arena.dataAlign << std::endl;
    }

    
    Y_PRINTV(MetaPrevPowerOfTwo<1>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<2>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<3>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<4>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<5>::Value);
    std::cerr << std::endl;

    Y_PRINTV(MetaNextPowerOfTwo<0>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<1>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<2>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<3>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<4>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<5>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<40>::Value);

}
Y_UDONE()
