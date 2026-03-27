#include "y/memory/allocator/archon.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/core/pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"
#include "y/ability/collectable.hpp"

#include "y/type/destruct.hpp"
#include "y/exception.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {

        const char * const Archon:: CallSign = "Memory::Archon";
        const unsigned     Archon:: NumSlots;

        //______________________________________________________________________
        //
        //
        //! Archon implementation
        //
        //______________________________________________________________________
        class Archon:: Code : public Collectable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Core::PoolOf<Page> Slot_; //!< alias

            //__________________________________________________________________
            //
            //
            //! LRU cache of same blockShift/blockBytes based on Dyadic
            //
            //__________________________________________________________________
            class Slot : public Slot_, public Collectable
            {
            public:
                //______________________________________________________________
                //
                // Definitions
                //______________________________________________________________
                static const size_t One = 1; //!< alias

                //______________________________________________________________
                //
                // C++
                //______________________________________________________________

                //! initilialize with blockSize and Dyadic instance
                inline explicit Slot(const unsigned bs,
                                     Dyadic        &da) noexcept :
                Slot_(),
                blockShift(bs),
                allocation(da),
                blockBytes(One<<blockShift)
                {}

                //! cleanup
                inline virtual ~Slot() noexcept { purge(); }

                //______________________________________________________________
                //
                // Methods
                //______________________________________________________________

                //! use cached or new block
                inline void *get() {
                    return (size>0) ? memset( query(), 0, blockBytes) : allocation.acquireBlock(blockShift);
                }

                //! store used block
                inline void   put(void * const blockAddr) noexcept
                { assert(0!=blockAddr); store( Page::From(blockAddr) ); }

                inline void purge() noexcept
                { while(size) allocation.releaseBlock( query(), blockShift); }


                //! gc returning to Dyadic
                inline virtual void gc(const uint8_t amount) noexcept
                {
                    const size_t newSize = NewSize(amount,size);
                    Core::ListOf<Page> list;
                    Core::PoolToList::Make(list,*this);
                    list.sortByDecreasingAddress();
                    while(list.size>newSize)
                        allocation.releaseBlock(list.popHead(),blockShift);
                    Core::ListToPool::Make(*this,list);
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                const unsigned  blockShift; //!< the block shift
                Dyadic        & allocation; //!< dyadic instance
                const size_t    blockBytes; //!< 2^blockShift

            private:
                Y_Disable_Copy_And_Assign(Slot); //!< discarding
            };

            static const size_t NumBytes = NumSlots * sizeof(Slot); //!< inner bytes

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            explicit Code() :
            slots(0),
            wksp()
            {
                Memory::Dyadic &da = Memory::Dyadic::Instance();
                Coerce(slots) = static_cast<Slot *>( Y_BZero(wksp) ) - MinBlockShift;
                for(unsigned i=MinBlockShift;i<=MaxBlockShift;++i)
                    new (slots+i) Slot(i,da);
            }

            //! cleanup
            virtual ~Code() noexcept
            {
                for(unsigned blockShift=MaxBlockShift;blockShift>=MinBlockShift;--blockShift)
                    Destruct( &slots[blockShift] );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! acquire block from selected slot
            inline void * acquireBlock(const unsigned blockShift)
            {
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);

                return slots[blockShift].get();
            }

            //! release block to select slot
            inline void releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept
            {
                assert(0!=blockAddr);
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);
                slots[blockShift].put(blockAddr);
            }

            //! gc on all slots
            inline void gc(const uint8_t amount) noexcept
            {
                for(unsigned blockShift=MaxBlockShift;blockShift>=MinBlockShift;--blockShift)
                    slots[blockShift].gc(amount);
            }

            Slot * const     slots;

        private:
            Y_Disable_Copy_And_Assign(Code);
            void * wksp[ Alignment::WordsGEQ<NumBytes>::Count ];
        };

        namespace
        {
            static void * ArchonCode[ Alignment::WordsFor<Archon::Code>::Count ];
        }

        Archon:: Archon()  : Singleton<Archon,Policy>(),
        code( new ( Y_BZero(ArchonCode) ) Code() )
        {
            assert(0!=code);
        }


        Archon:: ~Archon() noexcept
        {
            assert(0!=code);
            Destruct(code);
            Y_BZero(ArchonCode);
            Coerce(code) = 0;
        }


        void * Archon:: acquireBlock(const unsigned blockShift)
        {
            // sanity check
            assert(0!=code);
            assert(blockShift>=MinBlockShift);

            // locked acquire
            Y_Lock(access);
            return code->acquireBlock(blockShift);
        }

        void   Archon:: releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept
        {
            // sanity check
            assert(0!=code);
            assert(blockShift>=MinBlockShift);

            // locked release
            Y_Lock(access);
            code->releaseBlock(blockAddr,blockShift);
        }


        void * Archon:: acquire(size_t & blockSize)
        {
            // sanity check
            assert(code);
            if(blockSize>MaxBlockBytes) throw Specific::Exception(CallSign,"blockSize overflow");
            const unsigned blockShift = CeilLog2( Max(blockSize,MinBlockBytes) );

            // locked acquire
            Y_Lock(access);
            try
            {
                static const size_t _1 = 1;
                void * const p = code->acquireBlock(blockShift);
                blockSize = _1 << blockShift;
                return p;
            }
            catch(...)
            {
                blockSize = 0;
                throw;
            }
        }

        void Archon:: release(void * & blockAddr, size_t &blockSize) noexcept
        {
            // sanity check
            assert(code); assert(0!=blockAddr); assert( IsPowerOfTwo(blockSize) );
            const unsigned blockShift = ExactLog2(blockSize);
            assert(blockShift>=MinBlockShift);
            assert(blockShift<=MaxBlockShift);

            // locked release
            Y_Lock(access);
            code->releaseBlock(blockAddr,blockShift);
            blockAddr = 0;
            blockSize = 0;
        }

        void Archon:: gc(const uint8_t amount) noexcept
        {
            assert(code);
            Y_Lock(access);
            code->gc(amount);
        }


    }
}


#include "y/stream/xmlog.hpp"
namespace Yttrium
{
    namespace Memory
    {
        void Archon:: toXML(XML::Log &xml) const
        {
            assert(code);
            Y_XML_Element_Attr(xml,MemoryArchon, Y_XML_Attr(NumSlots));
            for(unsigned bs=MinBlockShift;bs<=MaxBlockShift;++bs)
            {
                const Code::Slot &slot = code->slots[bs];
                if(slot.size)
                {
                    const size_t bs       = slot.blockBytes;
                    const size_t available = slot.size;
                    Y_XML_Standalone(xml,Slot, Y_XML_Attr_Setw(bs,6) << Y_XML_Attr(available) );
                }
            }
        }
    }

}
