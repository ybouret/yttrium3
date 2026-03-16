

//! \file

#ifndef Y_Libc_Strfmt_Included
#define Y_Libc_Strfmt_Included

#include "y/config/setup.h"
//#include "y/check/printf.h"

#if defined(__cplusplus)
#include <cstdarg>
extern "C" {
#else
#include <stdarg.h>
#endif

    //__________________________________________________________________________
    //
    //! wrapper call to vsnprintf
    /**
     \param buffer target string
     \param buflen target total bytes
     \param fmt    valid format string
     \param app    address of a va_list
     \return vsnprintf result
     */
    //__________________________________________________________________________
    int Yttrium_Strfmt(char * const       buffer,
                       const size_t       buflen,
                       const char * const fmt,
                       va_list * const    app);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_Strfmt_Included
