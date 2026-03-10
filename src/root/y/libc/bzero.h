
//! \file

#ifndef Y_Libc_BZero_Included
#define Y_Libc_BZero_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    void * Yttrium_BZero(void * const addr, const size_t size);
    
    
   
    
#if defined(__cplusplus)
}
#endif

#define Y_BZero(BLOCK) Yttrium_BZero(BLOCK,sizeof(BLOCK))
#define Y_VZero(VAR)   Yttrium_BZero(&VAR,sizeof(VAR))


#endif // !Y_Libc_BZero_Included
