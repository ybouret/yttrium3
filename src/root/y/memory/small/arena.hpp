
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            class Arena
            {
            public:
                static const size_t MinNumBlocks = 8;
                static const size_t MaxNumBlocks = 255;
                static const size_t MaxBlockSize;

                //!
                /**
                 \param bs 1<= bs <= MaxBlockSize
                 */
                Arena(const size_t bs);
                ~Arena() noexcept;

                size_t numBlocksFor(const size_t length) noexcept;

                const size_t blockSize; //!< common block size for all chunks
                const size_t dataAlign; //!< offset to data chunk
                
            private:
                Y_Disable_Copy_And_Assign(Arena);
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
