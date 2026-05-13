#include "y/libc/pq/api.h"
#include "y/libc/block/swap.h"
#include <assert.h>
#include <string.h>


void Yttrium_PQ_Push_Balance(void * const   blockAddr,
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

        while(ipos>0)
        {
            const size_t ppos = (ipos-1)>>1;
            void * const i    = heap + blockSize * ipos;
            void * const p    = heap + blockSize * ppos;
            assert(i!=p);
            if( compare(p,i,args) < 0) break;
            Yttrium_BSwap(p,i,blockSize);
            ipos = ppos;
        }

    }

}

static void PQ_transfer(char *       target,
                        char *       source,
                        const size_t length)
{
    for(size_t i=length;i>0;--i)
    {
        *(target++) = *source;
        *(source++) = 0;
    }
}


void Yttrium_PQ_Pull_Balance(void * const   blockAddr,
                             const size_t   numBlocks,
                             const size_t   blockSize,
                             YttriumCompare compare,
                             void * const   args)
{
    assert(NULL!=blockAddr);
    assert(blockSize>0);
    assert(compare);

    if(numBlocks>0)
    {
        char * const heap = (char *)blockAddr;
        size_t       ipos = 0;
        size_t       lpos = 1;
        size_t       rpos = 2;

        PQ_transfer(heap,heap+numBlocks*blockSize,blockSize);
        while(1)
        {
            char * const i    = heap + ipos * blockSize;
            char * const l    = heap + lpos * blockSize;
            char * const r    = l+blockSize;
            char *       m    = 0;
            size_t       mpos = 0;

            if( (lpos<numBlocks) && (compare(l,i,args)<0) ) { mpos = lpos; m = l; }
            else                                            { mpos = ipos; m = i; }
            if( (rpos<numBlocks) && (compare(r,m,args)<0) ) { mpos = rpos; m = r; }
            if(mpos==ipos) { assert(i==m); return; }

            Yttrium_BSwap(m,i,blockSize);
            rpos = (ipos=mpos)<< 1;
            lpos = ++rpos;
            ++rpos;
        }

    }
}
