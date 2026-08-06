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
            static const unsigned MANT_DIG;   //!< mantissa digits
            static const unsigned MANT_DIG32; //!< min(32,MANT_DIG)
            static const uint32_t MAX_UINT32; //!< 2^MANT_DIG32-1
            static const T        MANT_DEN32; //!< MAX_UINT32+1 = 2^MANT_DIG32
            static const T        HALF;       //!< 0.5

            typedef T (Metrics::*Build)(const uint32_t) const;

            static inline void Test()
            {
                std::cerr << "MANT_DIG   = " << MANT_DIG   << std::endl;
                std::cerr << "MANT_DIG32 = " << MANT_DIG32 << std::endl;
                std::cerr << "MAX_UINT32 = " << Hexadecimal(MAX_UINT32) << std::endl;
                std::cerr << "MANT_DEN32 = " << MANT_DEN32 << std::endl;
                std::cerr << std::endl;
            }

            inline  Metrics(const uint32_t range) noexcept :
            max32(range),
            den32( getDen32() ),
            build( getBuild() )
            {
            }

            inline ~Metrics() noexcept {}



            inline T eval(const uint32_t u32) const noexcept
            {
                assert(u32<=max32);
                return (*this.*build)(u32);
            }

            inline void test(CoinFlip &coin) const
            {
                static const T one(1);
                std::cerr << std::setprecision(15);
                std::cerr << "-- max32 = " << max32 << std::endl;
                std::cerr << "-- den32 = " << den32 << std::endl;
                if(max32>MAX_UINT32)
                    std::cerr << "-- compressed" << std::endl;
                else
                    std::cerr << "-- full range" << std::endl;

                const T rmin = eval(0);
                std::cerr << "-- rmin = " << rmin << std::endl;
                const T rmax = eval(max32);
                std::cerr << "-- 1-rmax = " << one-rmax << std::endl;


                for(size_t i=0;i<10;++i)
                {
                    const uint32_t u32 = coin.toss(max32);
                    std::cerr << "\t" << Hexadecimal(u32) << " => " << eval(u32) << std::endl;
                }
                std::cerr << std::endl;
            }

            const uint32_t max32;
            const T        den32;
            Build const    build;

        private:
            Y_Disable_Copy_And_Assign(Metrics);

            inline T getDen32() const noexcept
            {

                if(max32>=MAX_UINT32)
                {
                    return MANT_DEN32;
                }
                else
                {
                    return (T) (max32+1);
                }
            }

            inline Build getBuild() const noexcept
            {
                if(max32>MAX_UINT32)
                {
                    std::cerr << "need compression" << std::endl;
                    return & Metrics:: getComp;
                }
                else
                {
                    std::cerr << "full range" << std::endl;
                    return & Metrics:: getFull;
                }
            }

            //! \return full range conversion
            inline T getFull(const uint32_t u32) const noexcept
            {
                assert(u32<=max32);
                return ( HALF + (T) u32 ) / den32;
            }

            //! \return compressed range conversion
            inline T getComp(const uint32_t u32) const noexcept
            {
                assert(u32<=max32);
                uint64_t u64 = u32;
                u64 *= MAX_UINT32;
                u64 /= max32;
                return getFull( (uint32_t) u64 );
            }


        };

        template <> const float       Metrics<float>       :: HALF = 0.5f;
        template <> const double      Metrics<double>      :: HALF = 0.5;
        template <> const long double Metrics<long double> :: HALF = 0.5L;


        template <> const unsigned Metrics<float>       :: MANT_DIG = FLT_MANT_DIG;
        template <> const unsigned Metrics<double>      :: MANT_DIG = DBL_MANT_DIG;
        template <> const unsigned Metrics<long double> :: MANT_DIG = LDBL_MANT_DIG;

        template <> const unsigned Metrics<float>       :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Metrics<double>      :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Metrics<long double> :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;

        namespace
        {
            template <const unsigned M32> struct GetMAX32
            {
                static const uint32_t One = 1;
                static const uint32_t Value = (One<<M32)-One;
            };

            template <> struct GetMAX32<32>
            {
                static const uint32_t Value = 0xffffffff;
            };

        }

        template <> const uint32_t Metrics<float>       :: MAX_UINT32 = GetMAX32<MANT_DIG32>::Value;
        template <> const uint32_t Metrics<double>      :: MAX_UINT32 = GetMAX32<MANT_DIG32>::Value;
        template <> const uint32_t Metrics<long double> :: MAX_UINT32 = GetMAX32<MANT_DIG32>::Value;

        namespace
        {
            template <typename T, const unsigned M32> struct GetDENOM32
            {
                static const T Value;
            };

            template <typename T> struct GetDENOM32<T,32>
            {
                static const T Value;
            };

            template <typename T, unsigned M32>
            const T GetDENOM32<T,M32>:: Value = uint32_t(1) << M32;

            template <typename T>
            const T GetDENOM32<T,32>:: Value = 4294967296;
        }

        template <> const float       Metrics<float>       :: MANT_DEN32 = GetDENOM32<float,MANT_DIG32>::Value;
        template <> const double      Metrics<double>      :: MANT_DEN32 = GetDENOM32<double,MANT_DIG32>::Value;
        template <> const long double Metrics<long double> :: MANT_DEN32 = GetDENOM32<long double,MANT_DIG32>::Value;


#endif

    }

}

using namespace Yttrium;

namespace
{
    template <typename T>
    void computeMetrics()
    {
        static const T eps   = MKL::Numeric<T>::EPSILON;
        static const T half  = 0.5f;
        static const T one   = 1;
        static const T top32 = half/eps-one;
        Y_PRINTV(eps);
        Y_PRINTV(top32);

        std::cerr << std::endl;
    }
}


Y_UTEST(random_metrics)
{
    Core::Rand ran;

#if 0
    Random::Metrics<float>::Test();

    { Random::Metrics<float> fm(0xff);   fm.test(ran);     }
    { Random::Metrics<float> fm(0xffff);  fm.test(ran);     }
    return 0;
    { Random::Metrics<float> fm(0xffffff);  fm.test(ran);     }
    { Random::Metrics<float> fm(0xfffffff); fm.test(ran);     }
#endif


    computeMetrics<float>();
    computeMetrics<double>();
    computeMetrics<long double>();

}
Y_UDONE()

