
#include "y/libc/memory.h"
#include <string.h>
#include <assert.h>

void * Yttrium_BZero(void * const addr, const size_t size)
{
    assert(!(NULL==addr&&size>0));
    return memset(addr,0,size);
}


void * Yttrium_BCopy(void * const       target,
                     const void * const source,
                     const size_t       length)
{
    assert(!(NULL==target&&length>0));
    assert(!(NULL==source&&length>0));
    return memcpy(target,source,length);
}

void * Yttrium_BMove(void * const       target,
                     const void * const source,
                     const size_t       length)
{
    assert(!(NULL==target&&length>0));
    assert(!(NULL==source&&length>0));
    return memmove(target,source,length);
}


void  Yttrium_BSwap(void * const target,
                    void * const source,
                    const size_t length)
{
    assert(!(NULL==target&&length>0));
    assert(!(NULL==source&&length>0));

    {
        uint8_t *tgt = (uint8_t *)target;
        uint8_t *src = (uint8_t *)source;
        for(size_t i=length;i>0;--i)
        {
            const uint8_t tmp = *tgt;
            *(tgt++) = *(src);
            *(src++) = tmp;
        }
    }

}


int   Yttrium_Zeroed(const void * const blockAddr,
                     const size_t       blockSize)
{
    assert(!(NULL==blockAddr&&blockSize>0));

    {
        uint8_t *p = (uint8_t *)blockAddr;
        for(size_t i=blockSize;i>0;--i)
        {
            if( 0 != *(p++) ) return 0;
        }
        return 1;
    }
}
