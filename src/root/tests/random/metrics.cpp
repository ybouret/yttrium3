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
            static const T        MANT_DEN32;

            static void Test()
            {
                std::cerr << "MANT_DIG   = " << MANT_DIG   << std::endl;
                std::cerr << "MANT_DIG32 = " << MANT_DIG32 << std::endl;
                std::cerr << "MANT_DEN32 = " << MANT_DEN32 << std::endl;
                std::cerr << std::endl;
            }
            
        private:
            Y_Disable_Copy_And_Assign(Metrics);

        };

        template <> const unsigned Metrics<float>       :: MANT_DIG = FLT_MANT_DIG;
        template <> const unsigned Metrics<double>      :: MANT_DIG = DBL_MANT_DIG;
        template <> const unsigned Metrics<long double> :: MANT_DIG = LDBL_MANT_DIG;

        template <> const unsigned Metrics<float>       :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Metrics<double>      :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Metrics<long double> :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;

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
    Random::Metrics<float>      ::Test();
    Random::Metrics<double>     ::Test();
    Random::Metrics<long double>::Test();

}
Y_UDONE()

