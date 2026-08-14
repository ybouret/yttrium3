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
            typedef T (Metrics::*Get)(const uint32_t) const;

            static const T        EPSILON; //!< numeric epsilon
            static const unsigned MAX_SHL; //!< theoretical denom : 2^MAX_SHL
            static const unsigned TOP_SHL; //!< min(32,MAX_SHL)
            static const uint32_t TOP_U32; //!< 2^TOP_SHL - 1
            static const T        TOP_DEN; //!< 2^TOP_SHL
            static const T        HALF;    //!< 0.5

            inline Metrics(const uint32_t umax) noexcept :
            m32(umax),
            d32( chooseD32() ),
            get( chooseGet() )
            {

            }

            inline ~Metrics() noexcept
            {

            }

            const uint32_t m32;
            const T        d32;
            Get const      get;

        private:
            Y_Disable_Copy_And_Assign(Metrics);

            inline T chooseD32() const noexcept
            {
                if(m32<TOP_U32)
                {
                    std::cerr << "Cut D32 @" << ( (T)m32+1 ) << std::endl;
                    return (T) m32+1;
                }
                else
                {
                    std::cerr << "Top D2 @" << TOP_DEN << std::endl;
                    return TOP_DEN;
                }
            }

            inline Get chooseGet() const noexcept
            {
                if(m32<=TOP_U32)
                    return & Metrics:: getFull;
                else
                    return & Metrics:: getComp;
            }

            T getFull(const uint32_t u32) const noexcept
            {
                return ( HALF + (T)u32 ) / d32;

            }

            T getComp(const uint32_t u32) const noexcept
            {
                uint64_t u64 = u32;
                u64 *= TOP_U32;
                u64 /= m32;
                return getFull( (uint32_t) u64 );

            }

        };

        template <> const float       Metrics<float>       :: EPSILON = FLT_EPSILON;
        template <> const double      Metrics<double>      :: EPSILON = DBL_EPSILON;
        template <> const long double Metrics<long double> :: EPSILON = LDBL_EPSILON;

        template <> const float       Metrics<float>       :: HALF = 0.5f;
        template <> const double      Metrics<double>      :: HALF = 0.5;
        template <> const long double Metrics<long double> :: HALF = 0.5L;

        template <> const unsigned Metrics<float>::       MAX_SHL = (unsigned) floorf( - logf(FLT_EPSILON)  / logf(2.0f) - 1.0f );
        template <> const unsigned Metrics<double>::      MAX_SHL = (unsigned) floor(  - log(DBL_EPSILON)   / log(2.0)   - 1.0  );
        template <> const unsigned Metrics<long double>:: MAX_SHL = (unsigned) floorl( - logl(LDBL_EPSILON) / logl(2.0L) - 1.0L );

        template <> const unsigned Metrics<float>::       TOP_SHL = Min<unsigned>(MAX_SHL,32);
        template <> const unsigned Metrics<double>::      TOP_SHL = Min<unsigned>(MAX_SHL,32);
        template <> const unsigned Metrics<long double>:: TOP_SHL = Min<unsigned>(MAX_SHL,32);

        namespace
        {

            uint32_t GetTopU32(const unsigned top_shl) noexcept
            {
                assert(top_shl<=32);

                static const uint32_t one = 1;
                switch(top_shl)
                {
                    case 32: return 0xffffffff;
                    default: break;
                }
                return (one<<top_shl) - one;
            }


            template <typename T> static inline
            T GetTopDen(const unsigned top_shl) noexcept
            {
                assert(top_shl<=32);

                static const uint32_t one = 1;
                switch(top_shl)
                {
                    case 32: return (T) 4294967296;
                    default: break;
                }
                return (T)(one<<top_shl);
            };
        }

        template <> const uint32_t    Metrics<float>::       TOP_U32 = GetTopU32(TOP_SHL);
        template <> const uint32_t    Metrics<double>::      TOP_U32 = GetTopU32(TOP_SHL);
        template <> const uint32_t    Metrics<long double>:: TOP_U32 = GetTopU32(TOP_SHL);

        template <> const float       Metrics<float>::       TOP_DEN = GetTopDen<float>(TOP_SHL);
        template <> const double      Metrics<double>::      TOP_DEN = GetTopDen<double>(TOP_SHL);
        template <> const long double Metrics<long double>:: TOP_DEN = GetTopDen<long double>(TOP_SHL);




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
        Y_PRINTV( Random::Metrics<T>::MAX_SHL );
        Y_PRINTV( Random::Metrics<T>::TOP_SHL );
        Y_PRINTV( Random::Metrics<T>::TOP_U32 );
        Y_PRINTV( Random::Metrics<T>::TOP_DEN );
        Y_SIZEOF( Random::Metrics<T> );
        std::cerr << std::endl;
    }

    template <typename T> static inline
    void testMetrics(const uint32_t umax)
    {
        std::cerr << "-- \t\t test Metrics for <" << typeid(T).name() << ">, umax=" << umax << std::endl;
        Random::Metrics<T> rm(umax);

    }


}


Y_UTEST(random_metrics)
{
    Core::Rand ran;

    showMetrics<float>();
    showMetrics<double>();
    showMetrics<long double>();

    testMetrics<float>(0xff);
    testMetrics<float>(0xffff);
    testMetrics<float>(0xffffff);
    testMetrics<float>(0xffffffff); 

}
Y_UDONE()

