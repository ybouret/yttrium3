#include "y/libc/block/swap.h"
#include "y/config/compiler.h"
#include <string.h>
#include <assert.h>


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
