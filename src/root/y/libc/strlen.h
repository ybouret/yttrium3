
//! \file

#ifndef Y_Libc_Strlen_Included
#define Y_Libc_Strlen_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif
    
    //__________________________________________________________________________
    //
    //! string length
    /**
     \param buffer target string
     \return lenght of buffer, 0 if NULL
     */
    //__________________________________________________________________________
    size_t Yttrium_Strlen(const char * const buffer);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Strlen_Included
