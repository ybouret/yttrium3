
#include "y/memory/small/arena.hpp"
#include "y/memory/metrics.hpp"

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

            size_t Arena:: numBlocksFor(const size_t length) noexcept
            {
                assert(length>=dataAlign);
                return (length-dataAlign)/blockSize;
            }

            size_t Arena:: pageBytesFor(const size_t blocks) noexcept
            {
                const size_t required = dataAlign + blocks * blockSize;
                return NextPowerOfTwo(required);
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
