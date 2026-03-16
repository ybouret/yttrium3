
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/config/setup.hpp"
#include "y/memory/book.hpp"
#include "y/core/list.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            class Chunk;

            //__________________________________________________________________
            //
            //
            //
            //! Arena of multiple chunks with same block size
            //
            //
            //__________________________________________________________________
            class Arena
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unsigned MinNumBlocksLog2  = 4;                                            //!< to ensure MinNumBlocks is a power of two
                static const size_t   MinNumBlocks      = 1<<MinNumBlocksLog2;                          //!< minimum number of blocks per chunk
                static const size_t   MaxNumBlocks      = 255;                                          //!< maximum number of blocks per chunk
                static const unsigned MaxBlockSizeLog2  = Metrics::MaxPageShift - (1+MinNumBlocksLog2); //!< from MaxBlockSize<=MaxPageBytes/(1+MinNumBlocks)
                static const size_t   MaxBlockSize      = size_t(1) << MaxBlockSizeLog2;                //!< MaxBlockSize = 2^MaxBlockSizeLog2
                typedef Core::ListOf<Chunk> Chunks;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup from block size
                /**
                 \param bs   1<= bs <= MaxBlockSize
                 \param book to choose pages according to inner metrics
                 */
                Arena(const size_t bs, Book &book);

                //! cleanup
                ~Arena() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                size_t  lostBytesPerChunk() const noexcept; //!< compute lost bytes per chunk \return allocated - usable

                //! acquire a new block
                /**
                 - if some block is available:
                 -- test acquiring (perfect caching)
                 -- search by spiraling
                 - otherwise create and assert a new chunk
                 \return a zeroed block[blockSize[
                 */
                void   *acquire();

                //! release a previously acquired block
                void    release(void *blockAddr) noexcept;

                const Chunks & chunks() const noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t    blockSize; //!< block size per chunk
            private:
                Chunk *         acquiring;  //!< acquiring chunk
                Chunk *         releasing;  //!< releasing chunk
                Chunk *         empty;      //!< another empty chunk
                size_t          ready;      //!< ready blocks
                Chunks          clist;      //!< chunks ordered by increasing memory

            public:
                const size_t    numBlocks; //!< number of blocks per chunk [1:255]
                const size_t    dataAlign; //!< data alignment
                Memory::Pages & allocator; //!< for

            private:
                Y_Disable_Copy_And_Assign(Arena); //!< discarded
                Chunk * newChunk();               //!< prepare a new chunk \return new formatted chunk with available numBlocks

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                void  * acquireBlock(Chunk * const chunk) noexcept;
                void  * searchBoth(Chunk *lower, Chunk *upper) noexcept;
                void  * searchNext(Chunk *upper) noexcept;
                void  * searchPrev(Chunk *lower) noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
