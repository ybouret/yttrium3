
#include "y/memory/small/arena.hpp"
#include "y/memory/metrics.hpp"
#include "y/memory/small/chunk.hpp"
//#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            const size_t Arena:: MaxBlockSize = (Metrics::MaxPageBytes-sizeof(Chunk))/MinNumBlocks;

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

            Arena:: Arena(const size_t bs) :
            blockSize(bs),
            dataAlign( DataAlign(blockSize) )
            {
                assert(blockSize>0);
                assert(blockSize<=MaxBlockSize);
                
                
            }

        }

    }

}
