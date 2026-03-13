#include "y/memory/small/chunk.hpp"
#include "y/type/ints.hpp"
#include <cassert>
#include <cstring>


namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            Chunk:: ~Chunk() noexcept
            {
                //if(stillAvailable<providedBlocks) memset(data,0,last-data);
            }



            Chunk:: Chunk(const size_t  blockSize,
                          const uint8_t numBlocks,
                          void * const  blockAddr) noexcept :
            data( static_cast<uint8_t*>(blockAddr) ),
            last( data + blockSize * numBlocks ),
            firstAvailable(0),
            stillAvailable(numBlocks),
            providedBlocks(numBlocks),
            next(0),
            prev(0)
            {
                assert(blockSize>0);
                uint8_t * p = data;
                for(uint8_t i=0;i!=numBlocks; p += blockSize)
                    *p = ++i;
            }


            void * Chunk:: acquire(const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                assert(stillAvailable>0);
                assert(firstAvailable<providedBlocks);

                uint8_t * const p = data + (firstAvailable * blockSize);
                firstAvailable = *p; assert(firstAvailable<=providedBlocks);
                --stillAvailable;
                memset(p,0,blockSize);
                return p;
            }

            Ownership Chunk:: whose(const void * const p) const noexcept
            {
                assert(0!=p);
                if(p<data)
                    return OwnedByPrev;
                else
                {
                    if(p>=last)
                        return OwnedByNext;
                    else
                        return OwnedBySelf;
                }
            }

            void  Chunk:: release(void * const p, const size_t blockSize) noexcept
            {
                // sanity check
                assert(0!=p);
                assert(OwnedBySelf==whose(p));
                assert(blockSize>0);

                // find block to release
                uint8_t * const toRelease = static_cast<uint8_t *>(p); assert( 0 == ( (toRelease-data) % blockSize) );
                const ptrdiff_t available = (toRelease-data)/blockSize; assert(available >= 0); assert(available < (ptrdiff_t)providedBlocks);

                *toRelease     = firstAvailable;     // mark it
                firstAvailable = (uint8_t)available; // update firstAvailable
                ++stillAvailable;                    // update status
            }
        }

    }

}


