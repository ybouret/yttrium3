#include "y/memory/small/blocks.hpp"
#include "y/libc/block/zero.h"
#include "y/ability/lockable.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Small
        {
            const size_t Blocks:: TableSize;

            Blocks:: Blocks(Memory::Book &userBook,
                            Lockable     &userLock) noexcept:
            table(0),
            acquiring(0),
            releasing(0),
            book(userBook),
            arena( sizeof(Arena), book, userLock),
            house( arena ),
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
                        house.recycle( slot.popHead() );
                    }
                    Destruct( &slot );
                }
                Y_BZero(wksp);
            }

            bool Blocks:: owns(const void * const blockAddr,
                               size_t           & blockSize) const noexcept
            {
                for(size_t i=0;i<TableSize;++i)
                {
                    for(const Arena *a=table[i].head;a;a=a->next)
                    {
                        if(a->owns(blockAddr))
                        {
                            blockSize = a->blockSize;
                            return true;
                        }
                    }
                }
                return false;
            }

            Arena * Blocks:: newArena(const size_t blockSize)
            {
                return house.produce(blockSize,book,arena.access);
            }

            void * Blocks:: acquire(const size_t blockSize)
            {
                Y_Lock(arena.access);

                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);

                // find slot for blockSize
                Slot &slot = table[blockSize&TableMask];

                if(acquiring&&blockSize==acquiring->blockSize)
                {
                    // cached!
                    assert(slot.owns(acquiring));
                    return slot.moveToHead(acquiring)->acquire();
                }
                else
                {
                    // look for recorded blockSize
                    acquiring = 0;
                    for(Arena *a=slot.head;a;a=a->next)
                    {
                        if(blockSize==a->blockSize)
                            return slot.moveToHead(acquiring=a)->acquire();
                    }

                    // create a new arena
                    assert(0==acquiring);
                    return slot.pushHead( acquiring = newArena(blockSize) )->acquire();
                }
            }


            void Blocks:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                Y_Lock(arena.access);

                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);
                assert(0!=blockAddr);

                // find slot
                Slot &slot = table[blockSize&TableMask];

                if(releasing&&blockSize==releasing->blockSize)
                {
                    // cached!
                    assert(slot.owns(releasing));
                    slot.moveToHead(releasing)->release(blockAddr);
                }
                else
                {
                    for(Arena *a=slot.head;a;a=a->next)
                    {
                        if(blockSize==a->blockSize)
                            return slot.moveToHead(releasing=a)->release(blockAddr);
                    }
                    std::cerr << "*** Unknown address " << blockAddr << "+" << blockSize << std::endl;
                }

            }

            Arena & Blocks:: operator[](const size_t blockSize)
            {
                Y_Lock(arena.access);

                // find slot
                Slot &slot = table[blockSize&TableMask];

                // look for existing blockSize
                for(Arena *a=slot.head;a;a=a->next)
                {
                    if(blockSize==a->blockSize)
                        return *slot.moveToHead(a);
                }

                // not found, create a new one
                return *slot.pushHead( newArena(blockSize) );
            }

        }

    }

}

#include "y/stream/xmlog.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Small
        {

            void Blocks:: toXML(XML::Log &xml) const
            {
                Y_XML_Element_Attr(xml,blocks,Y_XML_Attr(TableSize));
                arena.toXML(xml);
                Y_XML_Element(xml,content);
                for(size_t i=0;i<TableSize;++i)
                {
                    const Slot &slot = table[i];
                    for(const Arena *a=slot.head;a;a=a->next)
                    {
                        a->toXML(xml);
                    }
                }
            }


        }

    }

}

