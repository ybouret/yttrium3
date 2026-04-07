
//! \file

#ifndef Y_Object_Drifter_Hideout_Included
#define Y_Object_Drifter_Hideout_Included 1

#include "y/object/drifter.hpp"
#include "y/core/pool.hpp"
#include "y/core/list.hpp"
#include "y/memory/page.hpp"
#include "y/memory/small/house.hpp"
#include "y/calculus/meta2.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{



    class Object:: Drifter:: Hideout
    {
    public:
        typedef Memory::Small::Arena       Arena;
        typedef Core::PoolOf<Memory::Page> Pool;

        class Node : public Pool
        {
        public:
            Node(Arena &) noexcept;
            ~Node()       noexcept;
            Arena & arena;
            Node *  next;
            Node *  prev;
        private:
            Y_Disable_Copy_And_Assign(Node);
        };

        typedef Core::ListOf<Node> Slot;

        static const size_t         BytesPerSlot = sizeof(Slot);                                         //!< alias
        static const size_t         DefaultBytes = Y_BLOCK_SIZE;                                         //!< inner static memory hint
        static const size_t         TableSize    = MetaPrevPowerOfTwo<DefaultBytes/BytesPerSlot>::Value; //!< inner static memory
        static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;                        //!< log2(TableSize)
        static const size_t         TableMask    = TableSize-1;                                          //!< x%TableSize == x&TableMask
        static const size_t         TableBytes   = TableSize * sizeof(Slot);                             //!< actual table bytes request
        static const size_t         TableWords   = Alignment::WordsGEQ<TableBytes>::Count;               //!< inner table words

    private:
        Y_Disable_Copy_And_Assign(Hideout);
        Slot * const slots;
        Arena        arena;
        
        void *       wksp[TableWords];
    };
}

#endif // !Y_Object_Drifter_Hideout_Included
