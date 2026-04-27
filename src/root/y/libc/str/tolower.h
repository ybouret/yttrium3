

//! \file

#ifndef Y_Libc_StrToLower_Included
#define Y_Libc_StrToLower_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! string to lower
    /**
     \param buffer target string
     \param buflen target elngth
     \return buffer
     */
    //__________________________________________________________________________
    char * Yttrium_StrToLower(char * const buffer, const size_t buflen);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_StrToLower_Included
