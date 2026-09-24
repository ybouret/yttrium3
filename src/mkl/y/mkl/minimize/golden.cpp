
#include "y/mkl/minimize/golden.hpp"
#include "y/core/secure.hpp"
#include "y/mkl/numeric.hpp"
#include "y/xml/element.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace
        {
            template <typename T>
            void GoldenSaveState(OutputStream &fp, const Triplet<T> &x, const Triplet<T> &f, const unsigned color)
            {
                fp("%.15g %.15g %u\n", (double)x[1], (double)f[1], color);
                fp("%.15g %.15g %u\n", (double)x[2], (double)f[2], color);
                fp("%.15g %.15g %u\n", (double)x[3], (double)f[3], color);
                fp("%.15g %.15g %u\n", (double)x[1], (double)f[1], color);
                fp << "\n";
            }
        }

#define real_t float
#include "golden.hxx"
#undef real_t

#define real_t double
#include "golden.hxx"
#undef real_t

#define real_t long double
#include "golden.hxx"
#undef real_t

#define real_t XReal<float>
#include "golden.hxx"
#undef real_t

#define real_t XReal<double>
#include "golden.hxx"
#undef real_t

#define real_t XReal<long double>
#include "golden.hxx"
#undef real_t


    }

}


