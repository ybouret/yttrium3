
#include "y/memory/small/arena.hpp"
#include "y/memory/small/chunk.hpp"
#include <iostream>

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
                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);
                size_t bytes = blockSize;
                while(bytes<sizeof(Chunk)) bytes += blockSize;
                return bytes;
            }

            static inline
            size_t PageBytes(const size_t blockSize,
                             const size_t dataAlign,
                             size_t &     numBlocks)
            {
                // initialize numBlocks
                static const size_t DefaultPageBytes = Metrics::DefaultBytes;
                const size_t        minLength        = blockSize * (numBlocks=Arena::MinNumBlocks) + dataAlign;

                //std::cerr << "blockSize=" << blockSize << std::endl;
                //std::cerr << "dataAlign=" << dataAlign << std::endl;
                //std::cerr << "minLength=" << minLength << std::endl;

                //! initialize pageBytes
                size_t pageBytes = (minLength>DefaultPageBytes) ? NextPowerOfTwo(minLength) : DefaultPageBytes;

                //! adjust pageBytes to get a fitting numBlocks
            COMPUTE_NUM_BLOCKS:
                numBlocks = (pageBytes - dataAlign)/blockSize;
                //std::cerr << "pageBytes = " << pageBytes << " / numBlocks=" << numBlocks << std::endl;
                assert(numBlocks>=Arena::MinNumBlocks);
                if(numBlocks>Arena::MaxNumBlocks)
                {
                    pageBytes >>= 1;
                    goto COMPUTE_NUM_BLOCKS;
                }

                return pageBytes;
            }


            Arena:: Arena(const size_t bs) :
            blockSize(bs),
            dataAlign( DataAlign(blockSize) ),
            numBlocks(0),
            pageBytes( PageBytes(blockSize,dataAlign,Coerce(numBlocks)) )
            {



            }

            size_t Arena:: lostBytes() const noexcept
            {
                return pageBytes - numBlocks*blockSize - (dataAlign-sizeof(Chunk));

            }

        }

    }

}
