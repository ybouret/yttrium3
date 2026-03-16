

//! \file

#ifndef Y_Libc_BMove_Included
#define Y_Libc_BMove_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! move bytes from anyregions
    /**
     \param target target memory
     \param source source memory
     \param length bytes to copy
     \return target
     */
    //__________________________________________________________________________
    void * Yttrium_BMove(void * const       target,
                         const void * const source,
                         const size_t       length);

    
#if defined(__cplusplus)
}
#endif




#endif // !Y_Libc_BMove_Included
