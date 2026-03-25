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

#if 0
                std::cerr << "sizeof(arena)   = " << sizeof(Arena)   << std::endl;
                std::cerr << "arena.blockSize = " << arena.blockSize << std::endl;
                std::cerr << "arena.numBlocks = " << arena.numBlocks << std::endl;
#endif
                
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

            void * Blocks:: acquire(const size_t blockSize)
            {
                Y_Lock(arena.access);

                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);

                Slot &slot = table[blockSize&TableMask];

                if(acquiring&&blockSize==acquiring->blockSize)
                {
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
                    return slot.pushHead( acquiring = house.produce(blockSize,book,arena.access) )->acquire();

                }
            }


            void Blocks:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                Y_Lock(arena.access);

                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);
                assert(0!=blockAddr);

                Slot &slot = table[blockSize&TableMask];
                if(releasing&&blockSize==releasing->blockSize)
                {
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
                Slot &slot = table[blockSize&TableMask];

                // look for existing blockSize
                for(Arena *a=slot.head;a;a=a->next)
                {
                    if(blockSize==a->blockSize)
                        return *slot.moveToHead(a);
                }

                // not found
                return *slot.pushHead( house.produce(blockSize,book,arena.access) );
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

