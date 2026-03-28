
extern "C" {
    uint64_t    Yttrium_mach_absolute_time();
    long double Yttrium_mach_calibrate(int * const);

}

namespace Yttrium
{
    namespace System
    {


        long double WallTime:: Calibrate()
        {

            Y_Giant_Lock();
            int               err = 0;
            const long double res = Yttrium_mach_calibrate(&err);
            if(res<0.0L)
                throw Mach::Exception(err,"mach_timebase_info");
            return res;

#if 0
            static const long double nano = 1.0e-9L
            Y_Giant_Lock();
            mach_timebase_info_data_t timebase;
            const kern_return_t       err = mach_timebase_info(&timebase);
            if(KERN_SUCCESS!=err)
            {
                throw Mach::Exception(err,"mach_timebase_info");
            }
            const long double  conversion_factor = static_cast<long double>(timebase.numer) / timebase.denom;
            return nano * conversion_factor;
#endif
        }

        uint64_t WallTime:: Ticks()
        {
            return Yttrium_mach_absolute_time();
        }

    }

}

