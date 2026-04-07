
#include "y/object/drifter/hideout.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/nucleus.hpp"
#include "y/memory/small/blocks.hpp"
#include <cstring>

namespace Yttrium
{

    const char * const Object::Drifter:: Hideout:: CallSign = "Object::Drifter::Hideout";

    Object::Drifter:: Hideout:: Node:: Node(const size_t bs, Arena &a) noexcept :
    blockSize(bs),
    arena(a),
    next(0),
    prev(0)
    {
    }

    Object::Drifter:: Hideout:: Node:: ~Node() noexcept
    {
    }


    void * Object::Drifter:: Hideout:: Node:: acquire()
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

    Object::Drifter:: Hideout:: Hideout() :
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

    Object::Drifter:: Hideout:: ~Hideout() noexcept
    {

    }


    void * Object::Drifter::Hideout:: acquire(const size_t blockSize)
    {
        Y_Lock(access);
        assert(blockSize>0); // TODO: maxblocksize
        if(acquiring&&blockSize==acquiring->blockSize)
        {
            return acquiring->acquire();
        }
        else
        {
            Slot & slot = slots[blockSize&TableMask];
            for(Node *node=slot.head;node;node=node->next)
            {
                if(blockSize==node->blockSize)
                    return slot.moveToHead(acquiring=node)->acquire();
            }
            
        }
    }


}
