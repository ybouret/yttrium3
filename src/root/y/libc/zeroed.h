//! \file

#ifndef Y_Libc_Zeroed_Included
#define Y_Libc_Zeroed_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! test is memory block is zeroed
    /**
     \param blockAddr block address
     \param blockSize block size
     \return Y_TRUE iff all zero, Y_FALSE otherwise
     */
    //__________________________________________________________________________
    int   Yttrium_Zeroed(const void * const blockAddr,
                         const size_t       blockSize);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Zeroed_Included
