
#include "y/memory/plastic/forge.hpp"
#include "y/memory/book.hpp"
#include "y/core/max.hpp"

#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

#include "y/exception.hpp"
#include "y/format/decimal.hpp"

#include "y/ability/lockable.hpp"
#include "y/swap.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {
            Forge:: Forge(Book     & userBook,
                          Lockable & userLock) noexcept :
            list(),
            empty(0),
            book(   userBook ),
            access( userLock )
            {

            }


            Forge:: ~Forge() noexcept
            {
                Y_Lock(access);
                while(list.size)
                    remove( list.popTail() );
            }

            const Forge::ListType * Forge:: operator->() const noexcept
            {
                return &list;
            }


            unsigned Forge:: ShiftFor(const size_t blockSize) noexcept
            {
                assert(blockSize<=MaxBlockSize);
                const size_t lower     = Max(ReservedSize + blockSize,MinimalSize);
                const size_t predicted = Max(lower,Metrics::DefaultBytes); assert(predicted<=MaxPageBytes);
                return CeilLog2(predicted);
            }

            Bricks * Forge:: newBricks(const unsigned shift)
            {
                assert(shift>= MinPageShift);
                assert(shift<= MaxPageShift);

                Pages &           alloc     = book[shift]; assert(shift==alloc.pageShift);
                void *    const   block     = alloc.get();
                char * const      dataAddr  = static_cast<char *>(block) + DataOffset;
                const size_t      dataSize  = alloc.pageBytes - DataOffset;

                return list.pushHead( new (block) Bricks(dataAddr,dataSize,shift) );
            }

            
            Bricks * Forge:: newBricksFor(const size_t blockSize)
            {
                return newBricks( ShiftFor(blockSize) );
            }




            void * Forge:: acquire(size_t &blockSize)
            {
                // sanity check
                if(blockSize>=MaxBlockSize)
                    throw Specific::Exception("Forge", "blockSize overflow");

                // LRU caching
                Y_Lock(access);
                for(Bricks *node=list.head;node;node=node->next)
                {
                    void * const p = node->acquire(blockSize);
                    if(p)
                    {
                        (void) list.moveToHead(node);
                        if(empty==node)
                            empty = 0;
                        return p;
                    }
                }

                {
                    void * const p = newBricksFor(blockSize)->acquire(blockSize);
                    assert(0!=p);
                    return p;
                }
            }

            void Forge:: remove(Bricks *const bricks) noexcept
            {
                assert(0!=bricks);
                assert(0==bricks->prev);
                assert(0==bricks->next);
                book[bricks->info].put( Destructed(bricks) );
            }

            void Forge:: release(void * &blockAddr,
                                 size_t &blockSize) noexcept
            {
                Y_Lock(access);
                assert(0!=blockAddr);
                assert(blockSize>0);
                Bricks *  node = Bricks::Release(blockAddr,blockSize);
                assert(list.owns(node));
                if( list.moveToHead(node)->areEmpty() )
                {
                    if(0==empty)
                    {
                        empty = node;
                    }
                    else
                    {
                        // wil remove the smallest by size or highest address
                        assert(empty->areEmpty());
                        switch( Sign::Of(empty->info,node->info) )
                        {
                            case Negative:
                                assert(empty->info<node->info);
                                break;

                            case __Zero__: assert(empty->info==node->info);
                                if(node<empty)
                                    Swap(node,empty);
                                assert(node>empty);
                                break;

                            case Positive:
                                assert(empty->info>node->info);
                                Swap(empty,node);
                                assert(empty->info<node->info);
                                break;
                        }

                        assert(node->info>empty->info || node>empty);
                        
                        remove( list.pop(node) );
                    }
                }

            }


        }

    }

}
