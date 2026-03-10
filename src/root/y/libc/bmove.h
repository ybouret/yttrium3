

//! \file

#ifndef Y_Libc_BMove_Included
#define Y_Libc_BMove_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif
    
    void * Yttrium_BMove(void * const       target,
                         const void * const source,
                         const size_t       length);

    
#if defined(__cplusplus)
}
#endif




#endif // !Y_Libc_BMove_Included
