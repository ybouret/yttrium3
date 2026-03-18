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
                std::cerr << "numBricks in " << pageSize << " bytes : " << numBricks << " => main bytes=" << (numBricks-2) * sizeof(Brick) << std::endl;
                return numBricks-1;
            }

            Bricks:: Bricks(void * const pageAddr, const size_t pageSize) noexcept :
            ngap(1),
            head( static_cast<Brick *>(pageAddr) ),
            tail( head + BrickTailOffset(pageSize) )
            {
                head->prev = 0;
                head->next = tail;
                head->used = 0;
                head->size = (static_cast<size_t>(tail-head)-1) * sizeof(Brick);

                tail->prev = head;
                tail->next = 0;
                tail->used = this;
                tail->size = 0;
            }


            Bricks:: ~Bricks() noexcept
            {
                assert(0==head->prev);
                assert(0==tail->next);
                assert(this==tail->used);

                for(const Brick *brick = head; brick != tail; brick=brick->next)
                {
                    if(brick->used)
                    {
                        assert(this==brick->used);
                        std::cerr << "*** Missing Brick[" << brick->size << "]" << std::endl;
                    }
                }

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
                if(ngap<=0)
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

                    // update states
                    brick->size = blockSize;
                    node->used  = 0;
                    node->updateSize();

                }
                else
                {
                    blockSize = brick->size;
                }
                return memset(p,0,blockSize);
            }


        }

    }

}

