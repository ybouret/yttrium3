#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/mkl/numeric.hpp"

#include "y/format/hexadecimal.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace Random
    {

#if 0
        template <typename T>
        class Metrics
        {
        public:
            static const T        EPSILON;
            static const unsigned MAX_SHIFT;
            static const unsigned NMAX;
            static const T        DMAX;

        };

        template <> const float       Metrics<float>       :: EPSILON = FLT_EPSILON;
        template <> const double      Metrics<double>      :: EPSILON = DBL_EPSILON;
        template <> const long double Metrics<long double> :: EPSILON = LDBL_EPSILON;

        template <> const unsigned Metrics<float>::       MAX_SHIFT = (unsigned) floorf( - logf(EPSILON) / logf(2.0f) - 1.0f );
        template <> const unsigned Metrics<double>::      MAX_SHIFT = (unsigned) floor(  - log(EPSILON)  / log(2.0)   - 1.0  );
        template <> const unsigned Metrics<long double>:: MAX_SHIFT = (unsigned) floorl( - logl(EPSILON) / logl(2.0L) - 1.0L );

        template <> const unsigned Metrics<float>::       NMAX = (MAX_SHIFT < 32 ? MAX_SHIFT : 32);
        template <> const unsigned Metrics<double>::      NMAX = (MAX_SHIFT < 32 ? MAX_SHIFT : 32);
        template <> const unsigned Metrics<long double>:: NMAX = (MAX_SHIFT < 32 ? MAX_SHIFT : 32);

        namespace
        {
            template <typename T, const unsigned N> struct GetDenom
            {
                static const T Value = (T) ( uint32_t(1) << N );
            };

            template <typename T> struct GetDenom<T,32>
            {
                static const T Value = (T) 4294967296;
            };
        }

        //template <> const float Metrics<float>:: DMAX = GetDenom<float,NMAX>::Value;
#endif



    }

}

using namespace Yttrium;

namespace
{

}


Y_UTEST(random_metrics)
{
    Core::Rand ran;

    Y_PRINTV( MKL::Numeric<float>::EPSILON );
    Y_PRINTV( MKL::Numeric<float>::DIG );

    Y_PRINTV( MKL::Numeric<double>::EPSILON );
    Y_PRINTV( MKL::Numeric<double>::DIG );

    Y_PRINTV( MKL::Numeric<long double>::EPSILON );
    Y_PRINTV( MKL::Numeric<long double>::DIG );

}
Y_UDONE()

