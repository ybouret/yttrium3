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

            static inline
            size_t CheckBytes(const size_t blockSize, const size_t numBlocks) noexcept
            {

                return numBlocks * blockSize;
            }

            Chunk:: Chunk(const size_t  blockSize,
                          const uint8_t numBlocks,
                          void * const  blockAddr) noexcept :
            data( static_cast<uint8_t*>(blockAddr) ),
            last( data + CheckBytes(blockSize,numBlocks) ),
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
            }

        }

    }

}


