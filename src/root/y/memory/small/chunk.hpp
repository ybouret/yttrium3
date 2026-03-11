//! \file

#ifndef Y_Memory_Small_Chunk_Included
#define Y_Memory_Small_Chunk_Included 1

#include "y/config/compiler.h"
#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            //! handling chunk on any given region of memory
            class Chunk
            {
            public:
                Chunk(const size_t  blockSize,
                      const uint8_t numBlocks,
                      void * const  blockAddr) noexcept;

                ~Chunk() noexcept;

                uint8_t * const data;
                uint8_t         firstAvailable;
                uint8_t         stillAvailable;
                uint8_t         employedBlocks;
                const uint8_t   providedBlocks;

            private:
                Y_Disable_Copy_And_Assign(Chunk);
            };
        }



    }
}


#endif // !Y_Memory_Small_Chunk_Included
