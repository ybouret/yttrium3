

//! \file

#ifndef Y_Libc_BCopy_Included
#define Y_Libc_BCopy_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif


    void * Yttrium_BCopy(void * const       target,
                         const void * const source,
                         const size_t       length);
    


#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_BCopy_Included
