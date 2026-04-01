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
            Lockable(),
            Logging(),
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

            void Blocks:: lock() noexcept
            {
                arena.access.lock();
            }


            void Blocks:: unlock() noexcept
            {
                arena.access.unlock();
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




            void Blocks:: fetch(Arena *&pArena, const size_t blockSize)
            {
                Y_Lock(arena.access);
                fetch_(pArena,blockSize);

            }
            void Blocks:: fetch_(Arena * &pArena, const size_t blockSize)
            {
                assert(0==pArena);
                
                // find slot
                Slot &slot = table[blockSize&TableMask];

                // look for existing blockSize
                for(Arena *a=slot.head;a;a=a->next)
                {
                    if(blockSize==a->blockSize)
                    {
                        pArena = slot.moveToHead(a);
                        return;
                    }
                }

                // not found, create a new one
                pArena = slot.pushHead( newArena(blockSize) );
            }

            Arena & Blocks:: operator[](const size_t blockSize)
            {
                Y_Lock(arena.access);
                Arena * p = 0;
                fetch_(p,blockSize);
                return *p;
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

