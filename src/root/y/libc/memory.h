
//! \file

#ifndef Y_Libc_Memory_Included
#define Y_Libc_Memory_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    void * Yttrium_BZero(void * const addr, const size_t size);
    
    void * Yttrium_BCopy(void * const       target,
                         const void * const source,
                         const size_t       length);

    void * Yttrium_BMove(void * const       target,
                         const void * const source,
                         const size_t       length);

    void  Yttrium_BSwap(void * const target,
                        void * const source,
                        const size_t length);

    int   Yttrium_Zeroed(const void * const blockAddr,
                         const size_t       blockSize);

#if defined(__cplusplus)
}
#endif

#define Y_BZero(BLOCK) Yttrium_BZero(BLOCK,sizeof(BLOCK))


#endif // !Y_Libc_Memory_Included
