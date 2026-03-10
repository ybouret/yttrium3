


//! \file

#ifndef Y_Libc_Strtrim_Included
#define Y_Libc_Strtrim_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //__________________________________________________________________________
    //
    //! trim trailing spaces
    /**
     \param buffer input/output string
     \return updated buffer
     */
    //__________________________________________________________________________
    char * Yttrium_Strtrim(char * const buffer);


#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Strtrim_Included
