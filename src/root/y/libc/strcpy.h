

//! \file

#ifndef Y_Libc_Strcpy_Included
#define Y_Libc_Strcpy_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! copy string
    /**
     \param buffer target string
     \param buflen target total bytes
     \param source source string
     \return updated buffer
     */
    //__________________________________________________________________________
    char * Yttrium_Strcpy(char * const       buffer,
                          const size_t       buflen,
                          const char * const source);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Strcpy_Included
