
#include "y/memory/small/arena.hpp"
#include "y/memory/small/chunk.hpp"
#include "y/calculus/meta2.hpp"
#include "y/memory/book.hpp"
#include "y/ability/lockable.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            const Arena::Chunks * Arena:: operator->() const noexcept
            {
                return &clist;
            }


            Arena:: ~Arena() noexcept
            {
                // cleanup
                while(clist.size)
                {
                    Chunk * const chunk = clist.popHead();
                    if(!chunk->isEmpty())
                    {
                        std::cerr << "** Memory::Arena[" << blockSize << "] missing #" << chunk->missing() << std::endl;
                    }
                    allocator.put(chunk);
                }
            }



            static inline
            size_t PageBytes(const size_t blockSize,
                             const size_t dataAlign,
                             size_t &     numBlocks) noexcept
            {
                //--------------------------------------------------------------
                //
                // initialize pageBytes using minimal content
                //
                //--------------------------------------------------------------
                static const size_t DefaultPageBytes = Metrics::DefaultBytes;
                const size_t        minLength        = blockSize * (numBlocks=Arena::MinNumBlocks) + dataAlign;
                size_t              pageBytes = (minLength>DefaultPageBytes) ? NextPowerOfTwo(minLength) : DefaultPageBytes;

                //--------------------------------------------------------------
                //
                // adjust pageBytes to get a fitting numBlocks
                //
                //--------------------------------------------------------------
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

            Arena:: Arena(const size_t userSize,
                          Book &       userBook,
                          Lockable &   userLock) :
            blockSize(userSize),
            access(userLock),
            acquiring(0),
            releasing(0),
            empty(0),
            ready(0),
            clist(),
            numBlocks(0),
            dataAlign( DataAlign(blockSize) ),
            allocator( userBook[ PageShift(blockSize,dataAlign,Coerce(numBlocks)) ] ),
            next(0),
            prev(0)
            {
                acquiring = releasing = newChunk();
            }

            size_t Arena:: lostBytesPerChunk() const noexcept
            {
                size_t res = allocator.pageBytes;
                res       -= numBlocks * blockSize;
                res       -= sizeof(Chunk);
                return res;
            }



            Chunk * Arena:: newChunk()
            {
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

                ready += numBlocks;
                return chunk;
            }

        }

    }

}



#include "y/system/error.hpp"
#include "y/format/decimal.hpp"
#include "y/ability/lockable.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            void *Arena:: acquireBlock(Chunk * const chunk) noexcept
            {
                //--------------------------------------------------------------
                // sanity check
                //--------------------------------------------------------------
                assert(0!=chunk);
                assert(chunk->stillAvailable);
                assert(ready>=chunk->stillAvailable);

                //--------------------------------------------------------------
                // update
                //--------------------------------------------------------------
                --ready;
                if(chunk==empty) empty = 0;

                //--------------------------------------------------------------
                // return block
                //--------------------------------------------------------------
                return (acquiring=chunk)->acquire(blockSize);
            }

            void * Arena:: searchPrev(Chunk *lower) noexcept
            {
                assert(0!=lower);
            TRY:
                if(lower->stillAvailable) return acquireBlock(lower);
                lower = lower->next;
                assert(0!=lower);
                goto TRY;
            }

            void * Arena:: searchNext(Chunk *upper) noexcept
            {
                assert(0!=upper);
            TRY:
                if(upper->stillAvailable) { return acquireBlock(upper); }
                upper = upper->next;
                assert(0!=upper);
                goto TRY;
            }

            void * Arena:: searchBoth(Chunk *lower, Chunk *upper) noexcept
            {
            SEARCH_BOTH:
                assert(0!=lower);
                assert(0!=upper);

                if(lower->stillAvailable)      return acquireBlock(lower);
                if( 0 == (lower=lower->prev) ) return searchNext(upper);
                assert(0!=lower);

                if(upper->stillAvailable)      return acquireBlock(upper);
                if( 0 == (upper=upper->next))  return searchPrev(lower);
                assert(0!=upper);

                goto SEARCH_BOTH;
            }


            void   *Arena:: acquire()
            {
                Y_Lock(access);

                assert(0!=acquiring);

                if(ready>0)
                {
                    if(acquiring->stillAvailable)
                        return acquireBlock(acquiring); // cached
                    else
                    {
                        Chunk * const lower = acquiring->prev;
                        Chunk * const upper = acquiring->next;
                        if(lower)
                            return upper ? searchBoth(lower,upper) : searchPrev(lower);
                        else
                            return searchNext(upper);
                    }
                }
                else
                {
                    assert(0==empty);
                    return acquireBlock( newChunk() );
                }

            }

        }

    }

}



namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            void Arena:: release(void * const blockAddr) noexcept
            {
                Y_Lock(access);
                
                assert(0!=blockSize);
                assert(0!=releasing);

                //--------------------------------------------------------------
                //
                // locate releasing
                //
                //--------------------------------------------------------------
                switch( releasing->whose(blockAddr) )
                {
                    case OwnedByPrev: do { releasing = releasing->prev; assert(releasing); } while( !releasing->owns(blockAddr) ); break;
                    case OwnedByNext: do { releasing = releasing->next; assert(releasing); } while( !releasing->owns(blockAddr) ); break;
                    case OwnedBySelf: break;
                }
                assert(0!=releasing);
                assert(releasing->owns(blockAddr));

                //--------------------------------------------------------------
                //
                // release and update
                //
                //--------------------------------------------------------------
                releasing->release(blockAddr,blockSize);
                ++ready;

                //--------------------------------------------------------------
                //
                // done if releasing is not empty
                //
                //--------------------------------------------------------------
                if(!releasing->isEmpty()) return;

                //--------------------------------------------------------------
                //
                // mark first empty if possible
                //
                //--------------------------------------------------------------
                if(0==empty) { empty = releasing; return; }


                //--------------------------------------------------------------
                //
                // process two empty chunks
                //
                //--------------------------------------------------------------
                assert(empty!=releasing);
                assert(empty->isEmpty());
                assert(ready>=2*numBlocks);

                // will remove highest address
                if(empty<releasing)
                    Swap(empty,releasing);
                assert(releasing<empty);

                // be careful with acquiring
                if(acquiring==empty)
                    acquiring = releasing;

                // remove empty
                allocator.put( clist.pop(empty) );

                // update status
                ready -= numBlocks;
                empty  = releasing;
            }

        }

    }

}


