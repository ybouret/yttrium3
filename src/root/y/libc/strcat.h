


//! \file

#ifndef Y_Libc_Strcat_Included
#define Y_Libc_Strcat_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! catenate string
    /**
     \param buffer target string
     \param buflen target total bytes
     \param source source string
     \return updated buffer
     */
    //__________________________________________________________________________
    char * Yttrium_Strcat(char * const       buffer,
                          const size_t       buflen,
                          const char * const source);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Strcat_Included
