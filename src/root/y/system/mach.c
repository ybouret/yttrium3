
#include "y/config/platform.h"

#if defined(Y_Darwin)
#include <mach/mach.h>

const char * Yttrium_mach_error_string(const int err)
{
    return mach_error_string(err);
}
#else

const char * Yttrium_mach_error_string(const int err)
{
    (void) err;
    return "";
}

#endif
