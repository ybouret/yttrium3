

//! \file

#ifndef Y_Libc_BCopy_Included
#define Y_Libc_BCopy_Included

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
    void * Yttrium_BCopy(void * const       target,
                         const void * const source,
                         const size_t       length);
    


#if defined(__cplusplus)
}
#endif

//! helper to copy static fields
#define Y_BCopy(FIELD,OBJECT) Yttrium_BCopy(FIELD,(OBJECT).FIELD,sizeof(FIELD))

#endif // !Y_Libc_BCopy_Included
