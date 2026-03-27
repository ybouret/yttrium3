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

        class Archon:: Code
        {
        public:
            typedef Core::PoolOf<Page> Slot_;

            class Slot : public Slot_
            {
            public:
                static const size_t One = 1;

                inline explicit Slot(const unsigned blockShift) noexcept :
                Slot_(), blockSize(One<<blockShift) {}

                inline virtual ~Slot() noexcept {}

                inline void * get() noexcept
                { assert(size>0); return memset( query(), 0, blockSize); }

                inline void   put(void * const blockAddr) noexcept
                { assert(0!=blockAddr); store( Page::From(blockAddr) ); }

                inline Slot * free(Dyadic       & dyadic,
                                 const unsigned blockShift) noexcept
                { while(size) dyadic.releaseBlock( query(), blockShift); return this; }

                inline void trim(const size_t   newSize,
                                 Dyadic       & dyadic,
                                 const unsigned blockShift) noexcept
                {
                    Core::ListOf<Page> list;
                    Core::PoolToList::Make(list,*this);
                    list.sortByDecreasingAddress();
                    while(list.size>newSize)
                        dyadic.releaseBlock(list.popHead(),blockShift);
                    Core::ListToPool::Make(*this,list);
                }

                inline void gc(const uint8_t  amount,
                               Dyadic       & dyadic,
                               const unsigned blockShift) noexcept
                {
                    trim( Collectable::NewSize(amount,size), dyadic, blockShift);
                }

                const size_t blockSize;
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
                    new (slots+i) Slot(i);
            }

            virtual ~Code() noexcept
            {
                for(unsigned blockShift=MaxBlockShift;blockShift>=MinBlockShift;--blockShift)
                    Destruct( slots[blockShift].free(dyadic,blockShift) );
            }

            inline void * acquireBlock(const unsigned blockShift)
            {
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);

                Slot & slot = slots[blockShift];
                return slot.size ? slot.get() : dyadic.acquireBlock(blockShift);
            }

            inline void releaseBlock(void * const blockAddr, const unsigned blockShift) noexcept
            {
                assert(0!=blockAddr);
                assert(blockShift>=MinBlockShift);
                assert(blockShift<=MaxBlockShift);
                slots[blockShift].put(blockAddr);
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
                    Y_XML_Standalone(xml,Slot, Y_XML_Attr_Setw(slot.blockSize,8) << Y_XML_Attr(slot.size) );
                }
            }
        }
    }

}
