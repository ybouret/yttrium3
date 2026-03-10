#include "y/libc/zeroed.h"
#include "y/libc/defs.h"
#include "y/config/compiler.h"

#include <assert.h>

int   Yttrium_Zeroed(const void * const blockAddr,
                     const size_t       blockSize)
{
    assert(!(NULL==blockAddr&&blockSize>0));

    {
        uint8_t *p = (uint8_t *)blockAddr;
        for(size_t i=blockSize;i>0;--i)
        {
            if( 0 != *(p++) ) return Y_FALSE;
        }
        return Y_TRUE;
    }
}
