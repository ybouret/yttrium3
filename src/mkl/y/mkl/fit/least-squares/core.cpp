#include "y/mkl/fit/least-squares/core.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            const char * CurvatureNamed:: Value(const CurvatureResult res) noexcept
            {
                switch(res)
                {
                        Y_Return_Named_Case(Straight);
                        Y_Return_Named_Case(Expanded);
                        Y_Return_Named_Case(Singular);
                }
                return Core::Unknown;
            }

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


