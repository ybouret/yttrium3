#include "y/libc/block/zero.h"
#include <string.h>
#include <assert.h>

void * Yttrium_BZero(void * const addr, const size_t size)
{
    assert(!(NULL==addr&&size>0));
    return memset(addr,0,size);
}




