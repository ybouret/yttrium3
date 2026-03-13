
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/memory/small/chunk.hpp"
#include "y/calculus/meta2.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            class Arena
            {
            public:
                static const size_t   MinNumBlocks   = 8;
                static const size_t   MaxNumBlocks   = 255;
                static const size_t   ChunkBytes     = sizeof(Chunk);
                static const size_t   ChunkExp2Bytes = MetaNextPowerOfTwo<ChunkBytes>::Value;
                static const unsigned ChunkExp2Shift = IntegerLog2<ChunkExp2Bytes>::Value;

                //!
                /**
                 \param bs 1<= bs <= MaxBlockSize
                 */
                Arena(const size_t bs);
                ~Arena() noexcept;

                size_t numBlocksFor(const size_t length) noexcept;
                size_t pageBytesFor(const size_t blocks) noexcept;

                const size_t blockSize; //!< common block size for all chunks
                const size_t dataAlign; //!< offset to data chunk
                
            private:
                Y_Disable_Copy_And_Assign(Arena);
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
