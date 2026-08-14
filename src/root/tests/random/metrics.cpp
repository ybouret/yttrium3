#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/mkl/numeric.hpp"

#include "y/format/hexadecimal.hpp"
#include <cfloat>

#include "y/core/min.hpp"


namespace Yttrium
{
    namespace Random
    {

        template <typename T>
        class Metrics
        {
        public:
            static const T        EPSILON;
            static const unsigned MAX_SHL;
            static const unsigned TOP_SHL;
        };

        template <> const float       Metrics<float>       :: EPSILON = FLT_EPSILON;
        template <> const double      Metrics<double>      :: EPSILON = DBL_EPSILON;
        template <> const long double Metrics<long double> :: EPSILON = LDBL_EPSILON;

        template <> const unsigned Metrics<float>::       MAX_SHL = (unsigned) floorf( - logf(FLT_EPSILON)  / logf(2.0f) - 1.0f );
        template <> const unsigned Metrics<double>::      MAX_SHL = (unsigned) floor(  - log(DBL_EPSILON)   / log(2.0)   - 1.0  );
        template <> const unsigned Metrics<long double>:: MAX_SHL = (unsigned) floorl( - logl(LDBL_EPSILON) / logl(2.0L) - 1.0L );

        template <> const unsigned Metrics<float>::       TOP_SHL = Min<unsigned>(MAX_SHL,32);
        template <> const unsigned Metrics<double>::      TOP_SHL = Min<unsigned>(MAX_SHL,32);
        template <> const unsigned Metrics<long double>:: TOP_SHL = Min<unsigned>(MAX_SHL,32);

#if 0
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
    template <typename T> static inline
    void showMetrics()
    {
        std::cerr << "-- \t\t Metrics for <" << typeid(T).name() << "> :" << std::endl;
        Y_PRINTV( Random::Metrics<T>::EPSILON );
        Y_PRINTV( Random::Metrics<T>::MAX_SHL);
        Y_PRINTV( Random::Metrics<T>::TOP_SHL);

        std::cerr << std::endl;
    }

}


Y_UTEST(random_metrics)
{
    Core::Rand ran;

    showMetrics<float>();
    showMetrics<double>();
    showMetrics<long double>();

}
Y_UDONE()

