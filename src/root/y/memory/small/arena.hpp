
//! \file

#ifndef Y_Memory_Small_Arena_Included
#define Y_Memory_Small_Arena_Included 1

#include "y/memory/small/chunk.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            class Arena
            {
            public:
                static const size_t HeaderBytes = sizeof(Chunk);
                //static const size_t HeaderShift = IntegerLog2<HeaderBytes>::Value;

                Arena(const size_t bs);
                ~Arena() noexcept;

                const size_t blockSize;

            private:
                Y_Disable_Copy_And_Assign(Arena);
            };
        }

    }

}

#endif // !Y_Memory_Small_Arena_Included
