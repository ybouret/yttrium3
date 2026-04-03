
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/memory/small/arena/metrics.hpp"
#include "y/config/setup.hpp"
#include "y/core/list.hpp"
#include "y/memory/metrics.hpp"

namespace Yttrium
{

    class Lockable;

    namespace XML { class Log; }

    namespace Memory
    {
        class Book;
        class Pages;

        namespace Small
        {
            class Chunk;

            //__________________________________________________________________
            //
            //
            //
            //! Arena of multiple chunks with same block size
            /**
             - LEVEL-2 cache
             - memory I/O is protected with Pages setup (LEVEL-1)
             - self I/O is protected by access
             */
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
                static const size_t   _1                = 1;                                            //!< alias
                static const unsigned MinNumBlocksLog2  = ArenaMetrics::MinNumBlocksLog2;               //!< to ensure MinNumBlocks is a power of two
                static const size_t   MinNumBlocks      = ArenaMetrics::MinNumBlocks;                   //!< minimum number of blocks per chunk
                static const size_t   MaxNumBlocks      = ArenaMetrics::MaxNumBlocks;                   //!< maximum number of blocks per chunk
                static const unsigned MaxBlockSizeLog2  = Metrics::MaxPageShift - (1+MinNumBlocksLog2); //!< from MaxBlockSize<=MaxPageBytes/(1+MinNumBlocks)
                static const size_t   MaxBlockSize      = _1 << MaxBlockSizeLog2;                       //!< MaxBlockSize = 2^MaxBlockSizeLog2
                static const size_t   DataLocation      = ArenaMetrics::DataLocation;                   //!< Chunk requires 5 * sizeof(void*)
                typedef Core::ListOf<Chunk> Chunks;                                                     //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup from block size
                /**
                 \param userSize 1<= bs <= MaxBlockSize
                 \param userBook PERSISTENT to choose Pages according to inner metrics
                 \param userLock PERSISTENT lock for memory operations
                 */
                Arena(const size_t  userSize,
                      Book        & userBook,
                      Lockable    & userLock);

                //! cleanup
                ~Arena() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                size_t  lostBytesInHeader() const noexcept; //!< lost bytes due to Chunk \return  DataAlign-sizeof(Chunk)
                size_t  lostBytesPerChunk() const noexcept; //!< compute lost bytes per chunk \return allocated - usable

                //! acquire a new block, thread safe thru access
                /**
                 - if some block is available:
                 -# test acquiring (perfect caching)
                 -# search by spiraling localilty
                 - otherwise create and assert a new chunk
                 \return a zeroed block[blockSize]
                 */
                void   *acquire();

                //! release a block, thread safe thru access
                /**
                 \param blockAddr a previously acquired block
                 */
                void    release(void *blockAddr) noexcept;

                //! access to inner chunks \return address of chunks
                const Chunks * operator->() const noexcept;

                //! check ownership \param blockAddr memory \return true if within one the chunks
                bool owns(const void * const blockAddr) const noexcept;

                //! specific toXML \param xml target
                void toXML(XML::Log &xml) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t     blockSize; //!< block size per chunk
                Lockable &       access;    //!< PERSISTENT access

            private:
                Chunk *         acquiring;  //!< acquiring chunk
                Chunk *         releasing;  //!< releasing chunk
                Chunk *         empty;      //!< another empty chunk
                size_t          ready;      //!< ready blocks
                Chunks          clist;      //!< chunks ordered by increasing memory

            public:
                const size_t    numBlocks; //!< number of blocks per chunk [1:255]
                //const size_t    dataAlign; //!< data alignment
                Memory::Pages & allocator; //!< for
                Arena *         next;      //!< for list
                Arena *         prev;      //!< for list

            private:
                Y_Disable_Copy_And_Assign(Arena); //!< discarded
                Chunk * newChunk();               //!< prepare a new chunk \return new formatted chunk with available numBlocks

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                void  * acquireBlock(Chunk * const chunk) noexcept;
                size_t  countReady() const noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
