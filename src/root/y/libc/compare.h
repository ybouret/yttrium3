
//! \file

#ifndef Y_Libc_Compare_Included
#define Y_Libc_Compare_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //! comparison function prototype
    typedef int (*YttriumCompare)(const void * const, const void * const, void * const);
    
#if defined(__cplusplus)
}
#endif


#endif // !Y_Libc_Compare_Included
