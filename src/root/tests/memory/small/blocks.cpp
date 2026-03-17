
#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/nucleus.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            class Blocks
            {
            public:
                typedef Core::ListOf<Arena> Slot;
                static const size_t         TableSize    = 256;
                static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;
                static const size_t         TableMask    = TableSize-1;
                static const size_t         TableBytes   = TableSize * sizeof(Slot);

            private:
                Y_Disable_Copy_And_Assign(Blocks);
            };

        }
    }
}

using namespace Yttrium;

Y_UTEST(memory_small_blocks)
{
    Concurrent::Nucleus &        nucleus = Concurrent::Nucleus::Instance();

    Y_SIZEOF(Memory::Small::Blocks::Slot);
    Y_PRINTV(Memory::Small::Blocks::TableSize);
    Y_PRINTV(Memory::Small::Blocks::TableMask);
    Y_PRINTV(Memory::Small::Blocks::TableBytes);

}
Y_UDONE()
