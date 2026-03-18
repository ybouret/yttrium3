
//! \file

#ifndef Y_Memory_Small_Blocks_Included
#define Y_Memory_Small_Blocks_Included 1

#include "y/memory/small/house.hpp"
#include "y/calculus/meta2.hpp"
#include "y/calculus/alignment.hpp"

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

                explicit Blocks(Memory::Book & userBook,
                                Lockable     & userLock) noexcept;
                virtual ~Blocks() noexcept;

                void * acquire(const size_t blockSize);
                void   release(void * const blockAddr, const size_t blockSize) noexcept;
                
                bool   owns(const void * const blockAddr, size_t &blockSize) const noexcept;

            private:
                Y_Disable_Copy_And_Assign(Blocks);

                Slot * const   table;
                Arena *        acquiring;
                Arena *        releasing;
                Memory::Book & book;
                Arena          arena; //!< arena to manage arenas
                House<Arena>   house;
                void *         wksp[TableWords];
            };
        }

    }

}

#endif // !Y_Memory_Small_Blocks_Included
