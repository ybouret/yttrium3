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
            }



            Chunk:: Chunk(const size_t  blockSize,
                          const uint8_t numBlocks,
                          void * const  blockAddr) noexcept :
            data( static_cast<uint8_t*>(blockAddr) ),
            last( data + blockSize * numBlocks ),
            firstAvailable(0),
            stillAvailable(numBlocks),
            providedBlocks(numBlocks)
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
                firstAvailable = *p; assert(firstAvailable<providedBlocks);
                --stillAvailable;
                memset(p,0,blockSize);
                return p;
            }

        }

    }

}


