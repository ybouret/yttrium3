
#include "y/memory/small/arena.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/nucleus.hpp"
#include "y/calculus/alignment.hpp"
#include "y/calculus/meta2.hpp"

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
                static const size_t         BytesPerSlot = sizeof(Slot);
                static const size_t         DefaultBytes = Y_BLOCK_SIZE;
                static const size_t         TableSize    = MetaPrevPowerOfTwo<DefaultBytes/BytesPerSlot>::Value;
                static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;
                static const size_t         TableMask    = TableSize-1;
                static const size_t         TableBytes   = TableSize * sizeof(Slot);
                static const size_t         TableWords   = Alignment::WordsGEQ<TableBytes>::Count;

                explicit Blocks() noexcept;
                virtual ~Blocks() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Blocks);

                Slot * const table;
                void * wksp[TableWords];
            };
        }

    }

}

#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            Blocks:: Blocks() noexcept:
            table(0),
            wksp()
            {
                Coerce(table) = static_cast<Slot *>( Y_BZero(wksp) );
                for(size_t i=0;i<TableSize;++i) new( table+i ) Slot();
            }

            Blocks:: ~Blocks() noexcept
            {
                for(size_t i=0;i<TableSize;++i)
                {
                    Slot &slot = table[i];
                    while(slot.size>0)
                    {
                        Arena * const arena = slot.popHead();
                    }
                    Destruct( &slot );
                }
                Y_BZero(wksp);
            }

        }
    }
}

using namespace Yttrium;

Y_UTEST(memory_small_blocks)
{
    Concurrent::Nucleus &        nucleus = Concurrent::Nucleus::Instance();


    Y_SIZEOF(Memory::Small::Blocks::Slot);
    Y_PRINTV(Memory::Small::Blocks::BytesPerSlot);
    Y_PRINTV(Memory::Small::Blocks::DefaultBytes);

    Y_PRINTV(Memory::Small::Blocks::TableSize);
    Y_PRINTV(Memory::Small::Blocks::TableMask);
    Y_PRINTV(Memory::Small::Blocks::TableBytes);
    Y_PRINTV(Memory::Small::Blocks::TableWords);

}
Y_UDONE()
