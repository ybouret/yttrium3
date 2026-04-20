
//! \file

#ifndef Y_Libc_RAM_Remove_Included
#define Y_Libc_RAM_Remove_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! copy bytes from non-overlapping regions
    /**
     \param target target memory
     \param source source memory
     \param length bytes to copy
     \return target
     */
    //__________________________________________________________________________
    void  Yttrium_Ram_Remove(void * const       target,
                             const size_t       itemIndx,
                             size_t * const     size,
                             const size_t       itemSize);



#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_RAM_Remove_Included
