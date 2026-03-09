
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
