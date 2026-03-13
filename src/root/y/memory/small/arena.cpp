
#include "y/memory/small/arena.hpp"
#include "y/memory/small/chunk.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            Arena:: ~Arena() noexcept
            {

            }

            static inline
            size_t DataAlign(const size_t blockSize) noexcept
            {
                size_t bytes = blockSize;
                while(bytes<sizeof(Chunk)) bytes += blockSize;
                return bytes;
            }



            Arena:: Arena(const size_t bs) :
            blockSize(bs),
            dataAlign( DataAlign(blockSize) )
            {
                assert(blockSize>0);
                


            }

        }

    }

}
