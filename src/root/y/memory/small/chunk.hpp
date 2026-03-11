//! \file

#ifndef Y_Memory_Small_Chunk_Included
#define Y_Memory_Small_Chunk_Included 1

#include "y/config/compiler.h"
#include "y/config/setup.hpp"
#include "y/memory/ownership.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            //__________________________________________________________________
            //
            //
            //
            //! handling chunk on any given region of memory
            //
            //
            //__________________________________________________________________
            class Chunk
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param blockSize positive block size
                 \param numBlocks [1:255] number of blocks
                 \param blockAddr enough memory for numBlocks*blockSize bytes
                 */
                Chunk(const size_t  blockSize,
                      const uint8_t numBlocks,
                      void * const  blockAddr) noexcept;

                //! cleanup
                ~Chunk() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! return a zeroed block
                /**
                 stillAvailable must be positive
                 \param blockSize current block size
                 \return a clear memory block
                 */
                void *    acquire(const size_t blockSize) noexcept;

                //! release a previously acquired block
                /**
                 \param p address of the block
                 \param blockSize current block size
                 */
                void      release(void * const p, const size_t blockSize) noexcept;

                //! memory location \param p given address \return ownership status
                Ownership whose(const void * const p) const noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                uint8_t * const       data;     //!< base memoery
                const uint8_t * const last;     //!< first invalid memory
                uint8_t         firstAvailable; //!< first available block address
                uint8_t         stillAvailable; //!< available blocks
                const uint8_t   providedBlocks; //!< initially provided blocks

            private:
                Y_Disable_Copy_And_Assign(Chunk); //!< discarded
            };
        }



    }
}


#endif // !Y_Memory_Small_Chunk_Included
