//! \file

#ifndef Y_Libc_Zeroed_Included
#define Y_Libc_Zeroed_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif


    int   Yttrium_Zeroed(const void * const blockAddr,
                         const size_t       blockSize);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Zeroed_Included
