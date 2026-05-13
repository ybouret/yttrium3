#include "y/libc/pq/api.h"
#include "y/libc/block/swap.h"
#include <assert.h>

#define heap_parent(npos) ((int)(((npos) - 1) / 2))
#define heap_left(npos) (((npos) * 2) + 1)
#define heap_right(npos) (((npos) * 2) + 2)

static size_t Parent(const size_t i) { return (i-1)>>1; }

void Yttrium_PQ_Balance(void * const   blockAddr,
                        const size_t   numBlocks,
                        const size_t   blockSize,
                        YttriumCompare compare,
                        void * const   args)
{
    assert(NULL!=blockAddr);
    assert(numBlocks>0);
    assert(blockSize>0);
    assert(compare);
    
    {
        char * const heap = (char *)blockAddr;
        size_t       ipos = numBlocks-1;
        size_t       ppos = Parent(ipos);

        while(ipos>0)
        {

            void * const p = heap + blockSize * ppos;
            void * const i = heap + blockSize * ipos;
            assert(i!=p);
            if( compare(p,i,args) < 0) break;
            Yttrium_BSwap(i,p,blockSize);
            ipos = ppos;
            ppos = Parent(ipos);
        }

    }

}
