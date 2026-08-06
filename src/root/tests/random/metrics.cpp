#include "y/utest/run.hpp"

#include "y/format/hexadecimal.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace Random
    {

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

            inline void test() const
            {
                std::cerr << "max32=" << Hexadecimal(max32) << std::endl;
                std::cerr << "den32=" << den32 << std::endl;
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

            inline T getFull(const uint32_t u32) const noexcept
            {
                return ( HALF + (T) u32 ) / den32;
            }

            inline T getComp(const uint32_t u32) const noexcept
            {
                return 0;
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




    }

}

using namespace Yttrium;



Y_UTEST(random_metrics)
{
    Random::Metrics<float>::Test();

    { Random::Metrics<float> fm(0xfffff);   fm.test();     }
    { Random::Metrics<float> fm(0xffffff);  fm.test();     }
    { Random::Metrics<float> fm(0xfffffff); fm.test();     }





}
Y_UDONE()

