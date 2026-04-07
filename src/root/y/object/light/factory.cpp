
#include "y/object/light/factory.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/system/error.hpp"
#include <cstring>
#include <cerrno>
#include "y/format/decimal.hpp"

namespace Yttrium
{

    const char * const LightObject:: Factory:: CallSign = "LightObject::Factory";

    LightObject:: Factory:: Node:: Node(const size_t bs, Arena &a) noexcept :
    blockSize(bs),
    arena(a),
    next(0),
    prev(0)
    {
    }

    LightObject:: Factory:: Node:: ~Node() noexcept
    {
        while(size>0)
        {
            arena.release( query() );
        }
    }


    void * LightObject:: Factory:: Node:: acquire()
    {
        if(size>0)
        {
            return memset(query(),0,blockSize);
        }
        else
        {
            return arena.acquire();
        }
    }

    void LightObject:: Factory:: Node :: release(void *const blockAddr) noexcept
    {
        assert(blockAddr);
        store( Memory::Page::From(blockAddr) );
    }

    LightObject:: Factory:: Factory() :
    acquiring(0),
    releasing(0),
    slots(0),
    blocks( *Concurrent::Nucleus::Instance().blocks ),
    nArena( blocks[sizeof(Node)] ),
    nHouse( nArena ),
    wksp()
    {
        Coerce(slots) = static_cast<Slot *>( Y_BZero(wksp) );
        for(size_t i=0;i<TableSize;++i)
        {
            new (slots+i) Slot();
        }
    }

    LightObject:: Factory:: ~Factory() noexcept
    {
        for(size_t i=0;i<TableSize;++i)
        {
            Slot &slot = slots[i];
            while(slot.size>0)
            {
                nHouse.recycle(slot.popHead());
            }
            assert(0==slot.size);
            assert(0==slot.head);
            Destruct(&slot);
        }
    }




    void * LightObject::Factory:: acquire(const size_t blockSize)
    {
        Y_Lock(access);
        assert(blockSize>0); // TODO: maxblocksize
        assert(slots);

        Slot & slot = slots[blockSize&TableMask];
        if(acquiring&&blockSize==acquiring->blockSize)
        {
            assert( slot.owns(acquiring) );
            return slot.moveToHead(acquiring)->acquire();
        }
        else
        {

            //------------------------------------------------------------------
            // look for node
            //------------------------------------------------------------------
            for(Node *node=slot.head;node;node=node->next)
            {
                if(blockSize==node->blockSize)
                    return slot.moveToHead(acquiring=node)->acquire();
            }
            
            //------------------------------------------------------------------
            // need a new node
            //------------------------------------------------------------------
            const size_t minBlockSize = Max(blockSize,sizeof(Memory::Page));
            const size_t theBlockSize = minBlockSize; // TODO: align
            Node * const node         = nHouse.produce(blockSize,blocks[theBlockSize]);
            return slot.pushHead(acquiring=node)->acquire();
        }
    }

    void   LightObject:: Factory:: release(void * const blockAddr, const size_t blockSize) noexcept
    {
        Y_Lock(access);
        assert(0!=blockAddr); assert(blockSize>0);

        Slot & slot = slots[blockSize&TableMask];
        if(releasing&&blockSize==releasing->blockSize)
        {
            assert( slot.owns(releasing) );
            return slot.moveToHead(releasing)->release(blockAddr);
        }
        else
        {
            for(Node *node=slot.head;node;node=node->next)
            {
                if(blockSize==node->blockSize)
                    return slot.moveToHead(releasing=node)->release(blockAddr);
            }
            Libc::Error::Critical(EINVAL, "%s invalid release address/blockSize=%s", CallSign, Decimal(blockSize).c_str() );
        }
    }



}


#include "y/xml/log.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    void LightObject::Factory:: toXML(XML::Log &xml) const
    {
        Y_XML_Element(xml,LightObjectFactory);
        for(size_t i=0;i<TableSize;++i)
        {
            const Slot &slot = slots[i];
            for(const Node *node = slot.head;node;node=node->next)
            {
                if(node->size)
                {
                    Y_XML_Standalone(xml,Node,Y_XML_Attr(node->size));
                }
            }
        }
    }

}
