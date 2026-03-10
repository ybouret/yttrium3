#include "y/libc/bcopy.h"
#include <string.h>
#include <assert.h>
 

void * Yttrium_BCopy(void * const       target,
                     const void * const source,
                     const size_t       length)
{
    assert(!(NULL==target&&length>0));
    assert(!(NULL==source&&length>0));
    return memcpy(target,source,length);
}
