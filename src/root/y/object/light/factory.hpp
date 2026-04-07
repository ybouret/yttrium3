
//! \file

#ifndef Y_LightObject_Factory_Included
#define Y_LightObject_Factory_Included 1

#include "y/object/light.hpp"
#include "y/core/pool.hpp"
#include "y/core/list.hpp"
#include "y/memory/page.hpp"
#include "y/memory/small/house.hpp"
#include "y/calculus/meta2.hpp"
#include "y/calculus/alignment.hpp"

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/ability/logging.hpp"
//#include "y/ability/collectable.hpp"

namespace Yttrium
{

    namespace Memory { namespace Small { class Blocks; } }

    //__________________________________________________________________________
    //
    //
    //
    //! factory for LightObject
    //
    //
    //__________________________________________________________________________
    class LightObject:: Factory :
    public Singleton<Factory,ClassLockPolicy>,
    public Logging
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const          CallSign;                                   //!< "LightObject::Factory"
        static const Longevity             LifeTime = LifeTimeFor::LightObjectFactory; //!< alias
        typedef Memory::Small::Arena       Arena;                                      //!< alias
        typedef Memory::Small::Blocks      Blocks;                                     //!< alias
        typedef Core::PoolOf<Memory::Page> Pool;                                       //!< alias

        //______________________________________________________________________
        //
        //
        //! Node holding blocks of same blockSize, LEVEL-2 cache
        //
        //______________________________________________________________________
        class Node : public Pool //, public Collectable
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            typedef Memory::Small::House<Node> House; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            Node(const size_t, Arena &) noexcept; //!< setup with blockSize and matching arena
            virtual ~Node()             noexcept; //!< cleanup

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            void * acquireBlock();                      //!< \return cached/new block
            void   releaseBlock(void * const) noexcept; //!< release acquired block

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const size_t blockSize; //!< request by user
            Arena &      arena;     //!< arena.blockSize >= sizeof(MemoryPage), blockSize
            Node *       next;      //!< for pool/list
            Node *       prev;      //!< for list
        private:
            Y_Disable_Copy_And_Assign(Node); //!< discarded
        };
        typedef Core::ListOf<Node> Slot; //!< alias

        //______________________________________________________________________
        //
        //
        // Internal hash table metrics
        //
        //______________________________________________________________________
        static const size_t         BytesPerSlot = sizeof(Slot);                                         //!< alias
        static const size_t         DefaultBytes = Y_BLOCK_SIZE;                                         //!< inner static memory hint
        static const size_t         TableSize    = MetaPrevPowerOfTwo<DefaultBytes/BytesPerSlot>::Value; //!< inner static memory
        static const unsigned       TableSizeLn2 = IntegerLog2<TableSize>::Value;                        //!< ensure power-of-two
        static const size_t         TableMask    = TableSize-1;                                          //!< x%TableSize == x&TableMask
        static const size_t         TableBytes   = TableSize * sizeof(Slot);                             //!< actual table bytes request
        static const size_t         TableWords   = Alignment::WordsGEQ<TableBytes>::Count;               //!< inner table words

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void toXML(XML::Log &) const;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! acquire block \param blockSize block size \return matching block
        void * query(const size_t blockSize);

        //! release block and keep it \param blockAddr addres \param blockSize block size
        void   store(void * const blockAddr, const size_t blockSize) noexcept;

    private:
        Y_Disable_Copy_And_Assign(Factory); //!< discarded
        friend class Singleton<Factory,ClassLockPolicy>;
        Factory();                   //!< setup
        virtual ~Factory() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        Node *       acquiring;        //!< last acquiring
        Node *       releasing;        //!< last releasing
        Slot * const slots;            //!< slots[TableSize]
        Blocks     & blocks;           //!< all arenas
        Arena      & nArena;           //!< arena for Node
        Node::House  nHouse;           //!< house for Node
        void *       wksp[TableWords]; //!< inner memory
    };
}

#endif // !Y_LightObject_Factory_Included
