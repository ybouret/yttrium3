#include "y/memory/small/chunk.hpp"
#include <cassert>

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
            firstAvailable(0),
            stillAvailable(numBlocks),
            employedBlocks(0),
            providedBlocks(numBlocks)
            {
                assert(blockSize>0);
                uint8_t * p = data;
                for(uint8_t i=0;i!=numBlocks; p += blockSize)
                    *p = ++i;
            }

        }

    }

}


