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

        class Archon:: Code : public Collectable
        {
        public:
            typedef Core::PoolOf<Page> Slot_;

            class Slot : public Slot_, public Collectable
            {
            public:
                static const size_t One = 1;

                inline explicit Slot(const unsigned bs,
                                     Dyadic        &da) noexcept :
                Slot_(),
                blockShift(bs),
                allocation(da),
                blockBytes(One<<blockShift)
                {}

                inline virtual ~Slot() noexcept {}

                inline void *get() {
                    return size>0 ? memset( query(), 0, blockBytes) : allocation.acquireBlock(blockShift);
                }

                inline void   put(void * const blockAddr) noexcept
                { assert(0!=blockAddr); store( Page::From(blockAddr) ); }

                inline Slot * purge() noexcept
                { while(size) allocation.releaseBlock( query(), blockShift); return this; }

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

                const unsigned  blockShift;
                Dyadic        & allocation;
                const size_t    blockBytes;

            private:
                Y_Disable_Copy_And_Assign(Slot);
            };

            static const size_t NumBytes = NumSlots * sizeof(Slot);

            explicit Code() noexcept :
            slots(0),
            dyadic( Memory::Dyadic::Instance() ),
            wksp()
            {
                Coerce(slots) = static_cast<Slot *>( Y_BZero(wksp) ) - MinBlockShift;
                for(unsigned i=MinBlockShift;i<=MaxBlockShift;++i)
                    new (slots+i) Slot(i,dyadic);
            }

            virtual ~Code() noexcept
            {
                for(unsigned blockShift=MaxBlockShift;blockShift>=MinBlockShift;--blockShift)
                    Destruct( slots[blockShift].purge() );
            }

            inline void * acquireBlock(const unsigned blockShift)
            {
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);

                return slots[blockShift].get();
            }

            inline void releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept
            {
                assert(0!=blockAddr);
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);
                slots[blockShift].put(blockAddr);
            }

            inline void gc(const uint8_t amount) noexcept
            {
                for(unsigned blockShift=MaxBlockShift;blockShift>=MinBlockShift;--blockShift)
                    slots[blockShift].gc(amount);
            }

            Slot * const     slots;
            Memory::Dyadic & dyadic;

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
        }


        void * Archon:: acquireBlock(const unsigned blockShift)
        {
            assert(0!=code);
            Y_Lock(access);
            return code->acquireBlock(blockShift);
        }

        void   Archon:: releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept
        {
            assert(0!=code);
            Y_Lock(access);
            code->releaseBlock(blockAddr,blockShift);
        }


        void * Archon:: acquire(size_t & blockSize)
        {
            assert(code);
            if(blockSize>MaxBlockBytes) throw Specific::Exception(CallSign,"blockSize overflow");
            const unsigned blockShift = CeilLog2( Max(blockSize,MinBlockBytes) );
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
            assert(code);
            assert(0!=blockAddr);
            assert( IsPowerOfTwo(blockSize) );
            const unsigned blockShift = ExactLog2(blockSize);
            assert(blockShift>=MinBlockShift);
            assert(blockShift<=MaxBlockShift);
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
                    Y_XML_Standalone(xml,Slot, Y_XML_Attr_Setw(slot.blockBytes,6) << Y_XML_Attr(slot.size) );
                }
            }
        }
    }

}
