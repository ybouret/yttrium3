#include "y/mkl/fit/sample/probe.hpp"


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

#define real_t float
#include "probe.hxx"
#undef real_t

#define real_t double
#include "probe.hxx"
#undef real_t

#define real_t long double
#include "probe.hxx"
#undef real_t


#define real_t XReal<float>
#include "probe.hxx"
#undef real_t

#define real_t XReal<double>
#include "probe.hxx"
#undef real_t

#define real_t XReal<long double>
#include "probe.hxx"
#undef real_t


        }

    }

}


