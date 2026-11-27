#include "y/mkl/fit/least-squares/core.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            namespace
            {
                static const char LambdaName[] = "lambda";
            }
            
#define real_t float
#include "core.hxx"
#undef real_t

#define real_t double
#include "core.hxx"
#undef real_t

#define real_t long double
#include "core.hxx"
#undef real_t


#define real_t XReal<float>
#include "core.hxx"
#undef real_t

#define real_t XReal<double>
#include "core.hxx"
#undef real_t

#define real_t XReal<long double>
#include "core.hxx"
#undef real_t

        }

    }

}


