
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/config/setup.hpp"
#include "y/memory/metrics.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            class Chunk;

            class Arena
            {
            public:
                static const unsigned MinNumBlocksLog2  = 4;                    //!< to ensure MinNumBlocks is a power of two
                static const size_t   MinNumBlocks      = 1<<MinNumBlocksLog2;  //!< minimum number of blocks per chunk
                static const size_t   MaxNumBlocks      = 255;                  //!< maximum number of blocks per chunk
                static const unsigned MaxBlockSizeLog2  = Metrics::MaxPageShift - (1+MinNumBlocksLog2);
                static const size_t   MaxBlockSize      = size_t(1) << MaxBlockSizeLog2;
                //!
                /**
                 \param bs 1<= bs <= MaxBlockSize
                 */
                Arena(const size_t bs);
                ~Arena() noexcept;

                size_t  lostBytes() const noexcept;
                Chunk * format(void * const page) noexcept;

                const size_t  available; //!< total available blocks
                const size_t  blockSize; //!< common block size for all chunks
                const size_t  dataAlign; //!< data alignment
                const size_t  numBlocks; //!< number of blocks
                const size_t  pageBytes; //!< page used to hold chunk
                const size_t  newBlocks; //!< new blocks for a new chunk
                
            private:
                Y_Disable_Copy_And_Assign(Arena);
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
