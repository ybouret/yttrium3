#include "y/memory/plastic/bricks.hpp"
#include "y/memory/sentinel.hpp"

#include <cassert>
#include <iostream>
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        namespace Plastic
        {

            static   size_t BrickTailOffset(const size_t pageSize)
            {
                assert(pageSize>=Bricks::MinBlockSize);
                const size_t numBricks = pageSize / sizeof(Brick);
                assert(numBricks>=Bricks::MinPerPage+2);
                //std::cerr << "numBricks in " << pageSize << " bytes : " << numBricks << " => main bytes=" << (numBricks-2) * sizeof(Brick) << std::endl;
                return numBricks-1;
            }

#if !defined(NDEBUG)
            static bool CheckGapsOf(const Bricks * const bricks) noexcept
            {
                size_t count = 0;
                for(const Brick *node=bricks->head;node!=bricks->tail;node=node->next)
                {
                    if(0==node->used) ++count;
                }
                return count == bricks->ngap;
            }
#endif // !defined(NDEBUG)

            Bricks:: Bricks(void * const pageAddr, const size_t pageSize) noexcept :
            ngap(1),
            head( static_cast<Brick *>(pageAddr) ),
            tail( head + BrickTailOffset(pageSize) ),
            maxBlockSize((static_cast<size_t>(tail-head)-1) * sizeof(Brick)),
            next(0),
            prev(0)
            {
                head->prev = 0;
                head->next = tail;
                head->used = 0;
                head->size = maxBlockSize;

                tail->prev = head;
                tail->next = 0;
                tail->used = this;
                tail->size = 0;

                assert( CheckGapsOf(this) );
            }


            Bricks:: ~Bricks() noexcept
            {
                assert(0==head->prev);
                assert(0==tail->next);
                assert(this==tail->used);
                assert(CheckGapsOf(this));

                for(const Brick *brick = head; brick != tail; brick=brick->next)
                {
                    if(brick->used)
                    {
                        assert(this==brick->used);
                        std::cerr << "*** Missing Brick[" << brick->size << "]" << std::endl;
                    }
                }

            }



            bool Bricks:: ownsBrick(const Brick * const node) const noexcept
            {
                for(const Brick *brick = head; brick != tail; brick=brick->next)
                {
                    if(node==brick) return true;
                }
                return false;
            }


            bool Bricks:: areEmpty() const noexcept
            {
                if(0==head->used && head->next == tail )
                {
                    assert(head == tail->prev);
                    assert(1==ngap);
                    return true;
                }
                else
                    return false;
            }

            void * Bricks:: acquire(size_t &blockSize) noexcept
            {
                if(ngap<=0 || blockSize>maxBlockSize)
                    return 0; // full
                else
                {
                    const Brick * const last = tail;
                    for(Brick *brick=head;brick!=last;brick=brick->next)
                    {
                        if(brick->used) {
                            assert(this==brick->used);
                            continue; // in use
                        }

                        if(brick->size<blockSize)
                            continue; // too small

                        // successfull!
                        return deliver(brick,blockSize);

                    }

                    // all available gaps are too small
                    return 0;
                }
            }

            void * Bricks:: deliver(Brick * const brick, size_t &blockSize) noexcept
            {
                assert(brick);
                assert(0==brick->used);
                assert(brick->size>=blockSize);
                assert(CheckGapsOf(this));

                // mark brick as used
                brick->used = this;

                // normalize blockSize to minimal aligned value
                if(blockSize<=BrickBytes)
                {
                    blockSize = BrickBytes;
                }
                else
                {
                    assert(blockSize>BrickBytes);
                    const size_t rem = blockSize % BrickBytes;
                    if(rem)      blockSize += (BrickBytes-rem);

                    assert(0==(blockSize%BrickBytes));
                    assert(blockSize<=brick->size);
                }

                Brick * const p = brick+1;
                const size_t  xs = (brick->size-blockSize) / sizeof(Brick);
                if(xs>=2)
                {
                    // find new node
                    Brick * const node = &p[blockSize/sizeof(Brick)];
                    Brick * const next = brick->next;

                    // relink
                    brick->next = node;
                    node->prev  = brick;
                    node->next  = next;
                    next->prev  = node;

                    // update states, ngap is unchanged
                    brick->size = blockSize;
                    node->used  = 0;
                    node->updateSize();

                }
                else
                {
                    blockSize = brick->size;
                    --ngap;
                }
                assert( CheckGapsOf(this) );
                return memset(p,0,blockSize);
            }



            Bricks * Bricks:: Release(void * & blockAddr,
                                      size_t & blockSize) noexcept
            {
                static const unsigned FUSION_NONE = 0x00;
                static const unsigned FUSION_PREV = 0x01;
                static const unsigned FUSION_NEXT = 0x02;
                static const unsigned FUSION_BOTH = FUSION_PREV | FUSION_NEXT;

                // sanity check on input
                assert(0!=blockAddr);
                assert(blockSize>0);
                assert(0==(blockSize%sizeof(Brick)));

                // deduce brick and sanity check
                Brick * const  brick  = static_cast<Brick *>(blockAddr)-1;
                assert(0!=brick->used);
                assert(brick->size == blockSize);
                assert(brick->next);

                // check fusion status
                Bricks * const bricks = brick->used; assert(bricks->ownsBrick(brick));
                Brick * const  next   = brick->next;
                unsigned       flag = (0==next->used) ? FUSION_NEXT : FUSION_NONE;
                Brick * const  prev   = brick->prev; if(prev && 0==prev->used) flag |= FUSION_PREV;
                //std::cerr << "flag=" << flag << std::endl;

                // proceed with fusion
                switch(flag)
                {
                    case FUSION_NEXT: {
                        Brick * const post = next->next; assert(post);
                        brick->next = post;
                        post->prev  = brick; }
                        brick->updateSize();
                        brick->used = 0;
                        // no change in gaps
                        assert( CheckGapsOf(bricks) );
                        break;


                    case FUSION_PREV:
                        prev->next = next;
                        next->prev = prev;
                        prev->updateSize();
                        // no change in gaps
                        assert( CheckGapsOf(bricks) );
                        break;

                    case FUSION_BOTH: assert(bricks->ngap>=2); {
                        Brick * const post = next->next; assert(post);
                        prev->next = post;
                        post->prev = prev; }
                        prev->updateSize();

                        // decrease by one gap
                        --bricks->ngap;
                        assert( CheckGapsOf(bricks) );
                        break;

                    default:
                        assert(FUSION_NONE==flag);

                        // mark as free and increase ngap
                        brick->used = 0;
                        ++bricks->ngap;
                        assert( CheckGapsOf(bricks) );
                }

                blockAddr = 0;
                blockSize = 0;
                return bricks;
            }
        }

    }

}

