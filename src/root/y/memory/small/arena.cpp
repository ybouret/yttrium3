
#include "y/memory/small/arena.hpp"
#include "y/memory/small/chunk.hpp"
#include "y/calculus/meta2.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            Arena:: ~Arena() noexcept
            {
                while(clist.size)
                {
                    Chunk * const chunk = clist.popHead();
                    allocator.put(chunk);
                }
            }



            static inline
            size_t PageBytes(const size_t blockSize,
                             const size_t dataAlign,
                             size_t &     numBlocks) noexcept
            {
                // initialize pageBytes
                static const size_t DefaultPageBytes = Metrics::DefaultBytes;
                const size_t        minLength        = blockSize * (numBlocks=Arena::MinNumBlocks) + dataAlign;
                size_t              pageBytes = (minLength>DefaultPageBytes) ? NextPowerOfTwo(minLength) : DefaultPageBytes;

                // adjust pageBytes to get a fitting numBlocks
            COMPUTE_NUM_BLOCKS:
                numBlocks = (pageBytes - dataAlign)/blockSize;
                assert(numBlocks>=Arena::MinNumBlocks);
                if(numBlocks>Arena::MaxNumBlocks)
                {
                    pageBytes >>= 1;
                    goto COMPUTE_NUM_BLOCKS;
                }

                return pageBytes;
            }

            static inline
            unsigned PageShift(const size_t blockSize,
                               const size_t dataAlign,
                               size_t &     numBlocks) noexcept
            {
                const size_t pageBytes = PageBytes(blockSize,dataAlign,numBlocks);
                return ExactLog2(pageBytes);
            }


#if 0
            static inline
            size_t DataAlign(const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                assert(blockSize<=Arena::MaxBlockSize);
                size_t bytes = blockSize;
                while(bytes<sizeof(Chunk)) bytes += blockSize;
                return bytes;
            }
#else
            static inline size_t DataAlign(const size_t) noexcept
            {
                return MetaNextPowerOfTwo< sizeof(Chunk) >::Value;
            }
#endif

            Arena:: Arena(const size_t bs, Book & book) :
            blockSize(bs),
            acquiring(0),
            releasing(0),
            empty(0),
            ready(0),
            clist(),
            numBlocks(0),
            dataAlign( DataAlign(blockSize) ),
            allocator( book[ PageShift(blockSize,dataAlign,Coerce(numBlocks)) ] )
            {
                acquiring = releasing = newChunk();
                ready     = numBlocks;
            }

            size_t Arena:: lostBytesPerChunk() const noexcept
            {
                size_t res = allocator.pageBytes;
                res       -= numBlocks * blockSize;
                res       -= sizeof(Chunk);
                return res;
            }



            Chunk * Arena:: newChunk() {
                uint8_t * const zpage = static_cast<uint8_t*>( allocator.get() );
                Chunk *   const chunk = clist.pushTail( new (zpage) Chunk(blockSize, (uint8_t)numBlocks, zpage + dataAlign) );
                while(chunk->prev && chunk->prev>chunk) clist.towardsHead(chunk);

#if !defined(NDEBUG)
                for(const Chunk *node=clist.head;node;node=node->next)
                {
                    if(chunk->prev) { assert(chunk->prev<chunk); }
                    if(chunk->next) { assert(chunk<chunk->next); }
                }
#endif // !defined(NDEBUG)

                return chunk;
            }





        }

    }

}
