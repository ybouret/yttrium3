


//! \file

#ifndef Y_Libc_BSwap_Included
#define Y_Libc_BSwap_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! swap bytes in memory
    /**
     \param target target memory
     \param source source memory
     \param length bytes to copy
     */
    //__________________________________________________________________________
    void  Yttrium_BSwap(void * const target,
                        void * const source,
                        const size_t length);


#if defined(__cplusplus)
}
#endif




#endif // !Y_Libc_BSwap_Included
