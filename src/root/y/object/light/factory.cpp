
#include "y/object/light/factory.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include "y/system/error.hpp"
#include <cstring>
#include <cerrno>
#include "y/format/decimal.hpp"

#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"

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

    void LightObject:: Factory:: Node:: gc(const uint8_t amount) noexcept
    {
        Core::ListOf<Memory::Page> list;
        Core::PoolToList::Make(list,*this).sortByDecreasingAddress();
        {
            const size_t newSize = NewSize(amount,size);
            while(list.size>newSize) arena.release( list.popHead() );
        }
        Core::ListToPool::Make(*this,list);
    }



    void * LightObject:: Factory:: Node:: acquireBlock()
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

    void LightObject:: Factory:: Node :: releaseBlock(void *const blockAddr) noexcept
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




    void * LightObject::Factory:: query(const size_t blockSize)
    {
        Y_Lock(access);
        assert(blockSize>0); // TODO: maxblocksize
        assert(slots);

        Slot & slot = slots[blockSize&TableMask];
        if(acquiring&&blockSize==acquiring->blockSize)
        {
            assert( slot.owns(acquiring) );
            return slot.moveToHead(acquiring)->acquireBlock();
        }
        else
        {

            //------------------------------------------------------------------
            // look for node
            //------------------------------------------------------------------
            for(Node *node=slot.head;node;node=node->next)
            {
                if(blockSize==node->blockSize)
                    return slot.moveToHead(acquiring=node)->acquireBlock();
            }
            
            //------------------------------------------------------------------
            // need a new node
            //------------------------------------------------------------------
            const size_t minBlockSize = Max(blockSize,sizeof(Memory::Page));
            const size_t theBlockSize = minBlockSize; // TODO: align
            Node * const node         = nHouse.produce(blockSize,blocks[theBlockSize]);
            return slot.pushHead(acquiring=node)->acquireBlock();
        }
    }

    void   LightObject:: Factory:: store(void * const blockAddr, const size_t blockSize) noexcept
    {
        Y_Lock(access);
        assert(0!=blockAddr); assert(blockSize>0);

        Slot & slot = slots[blockSize&TableMask];
        if(releasing&&blockSize==releasing->blockSize)
        {
            assert( slot.owns(releasing) );
            return slot.moveToHead(releasing)->releaseBlock(blockAddr);
        }
        else
        {
            for(Node *node=slot.head;node;node=node->next)
            {
                if(blockSize==node->blockSize)
                    return slot.moveToHead(releasing=node)->releaseBlock(blockAddr);
            }
            Libc::Error::Critical(EINVAL, "%s invalid release address/blockSize=%s", CallSign, Decimal(blockSize).c_str() );
        }
    }

    void LightObject:: Factory:: gc(const uint8_t amount) noexcept
    {
        Y_Lock(access);
        releasing = 0;
        acquiring = 0;
        for(size_t i=0;i<TableSize;++i)
        {
            Slot &slot = slots[i];
            for(Node * node=slot.head;node;node=node->next)
            {
                node->gc(amount);
            }
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
                    const size_t available     = node->size;
                    const size_t nodeBlockSize = node->blockSize;
                    const size_t dataBlockSize = node->arena.blockSize;
                    Y_XML_Standalone(xml,LightObjectNode,
                                     /**/ Y_XML_Attr_Setw(available,4)
                                     <<   Y_XML_Attr_Setw(nodeBlockSize,3)
                                     <<   Y_XML_Attr_Setw(dataBlockSize,3));
                }
            }
        }
    }

}
