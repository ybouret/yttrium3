
#include "y/config/setup.h"

#if defined(Y_Darwin)

#include <mach/mach.h>
#include <mach/mach_time.h>


uint64_t Yttrium_mach_absolute_time()
{
    return mach_absolute_time();
}

long double Yttrium_mach_calibrate(int * const err)
{
    static const long double  nano = 1.0e-9L;
    mach_timebase_info_data_t timebase;
    const kern_return_t       errCode = mach_timebase_info(&timebase);
    if(KERN_SUCCESS != errCode)
    {
        *err = errCode;
        return -1.0L;
    }
    else
    {
        const long double  conversion_factor = (long double)(timebase.numer) / timebase.denom;
        return nano * conversion_factor;
    }
}


#else


uint64_t Yttrium_mach_absolute_time(void)
{
    return 0;
}

#endif

