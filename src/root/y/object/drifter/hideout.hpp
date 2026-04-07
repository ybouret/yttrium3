
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
#include "y/singleton.hpp"

namespace Yttrium
{

    namespace Memory { namespace Small { class Blocks; } }

    class Object:: Drifter:: Hideout : public Singleton<Hideout,ClassLockPolicy>
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = 100;

        typedef Memory::Small::Arena       Arena;
        typedef Memory::Small::Blocks      Blocks;
        typedef Core::PoolOf<Memory::Page> Pool;

        class Node : public Pool
        {
        public:
            typedef Memory::Small::House<Node> House;
            Node(const size_t, Arena &) noexcept;
            ~Node()       noexcept;

            void * acquire();

            const size_t blockSize;
            Arena &      arena;
            Node *       next;
            Node *       prev;
        private:
            Y_Disable_Copy_And_Assign(Node);
        };

        typedef Core::ListOf<Node> Slot;

        static const size_t         BytesPerSlot = sizeof(Slot);                                         //!< alias
        static const size_t         DefaultBytes = Y_BLOCK_SIZE;                                         //!< inner static memory hint
        static const size_t         TableSize    = MetaPrevPowerOfTwo<DefaultBytes/BytesPerSlot>::Value; //!< inner static memory
        static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;                        //!< ensure power-of-two
        static const size_t         TableMask    = TableSize-1;                                          //!< x%TableSize == x&TableMask
        static const size_t         TableBytes   = TableSize * sizeof(Slot);                             //!< actual table bytes request
        static const size_t         TableWords   = Alignment::WordsGEQ<TableBytes>::Count;               //!< inner table words


        void * acquire(const size_t blockSize);

    private:
        Y_Disable_Copy_And_Assign(Hideout);
        friend class Singleton<Hideout,ClassLockPolicy>;
        Hideout();
        virtual ~Hideout() noexcept;

        Node *       acquiring;
        Node *       releasing;
        Slot * const slots;
        Blocks     & blocks;
        Arena      & nArena;
        Node::House  nHouse;
        void *       wksp[TableWords];
    };
}

#endif // !Y_Object_Drifter_Hideout_Included
