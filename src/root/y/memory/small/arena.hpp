
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

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup from block size
                /**
                 \param bs 1<= bs <= MaxBlockSize
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
                size_t  lostBytes() const noexcept;         //!< compute lost bytes per chunk \return allocated - usable
                Chunk * format(void * const page) noexcept; //!< helper to format chunk \param page memory[pageBytes] \return ready chunk

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________

                const size_t        blockSize; //!< block size per chunk
            private:
                Chunk *             acquiring;  //!< acquiring chunk
                Chunk *             releasing;  //!< releasing chunk
                Chunk *             empty;      //!< another empty chunk
                size_t              ready;      //!< ready blocks
                Core::ListOf<Chunk> clist;      //!< chunks ordered by increasing memory

            public:
                const size_t        numBlocks; //!< number of blocks per chunk [1:255]
                const size_t        dataAlign; //!< data alignment
                Memory::Pages &     allocator; //!< for
                
            private:
                Y_Disable_Copy_And_Assign(Arena); //!< discarded
                Chunk * newChunk();
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
