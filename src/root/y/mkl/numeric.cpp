
#include "y/mkl/numeric.hpp"
#include <cmath>
#include <cfloat>
#include <climits>

namespace Yttrium
{
    namespace MKL
    {


#define Y_F(X) X##f
#define Y_D(X) X
#define Y_L(X) X##l
        
        template <> const float       Numeric<float> ::      PI = Y_F(3.14159265358979323846264338327950288419716939937510582);
        template <> const double      Numeric<double>::      PI = Y_D(3.14159265358979323846264338327950288419716939937510582);
        template <> const long double Numeric<long double>:: PI = Y_L(3.14159265358979323846264338327950288419716939937510582);



        template <> const unsigned Numeric<float>::      RADIX = FLT_RADIX;
        template <> const unsigned Numeric<double>::     RADIX = FLT_RADIX;
        template <> const unsigned Numeric<long double>::RADIX = FLT_RADIX;

        

        template <> const unsigned Numeric< XReal<float>  >      :: RADIX = FLT_RADIX;
        template <> const unsigned Numeric< XReal<double> >      :: RADIX = FLT_RADIX;
        template <> const unsigned Numeric< XReal<long double> > :: RADIX = FLT_RADIX;


#define Y_MKL_DECL_TYPE(TYPE,VAR) \
template <> const TYPE Numeric<float>                :: VAR = FLT_##VAR; \
template <> const TYPE Numeric<double>               :: VAR = DBL_##VAR; \
template <> const TYPE Numeric<long double>          :: VAR = LDBL_##VAR;\
template <> const TYPE Numeric< XReal<float> >       :: VAR = Numeric<float>  :: VAR;\
template <> const TYPE Numeric< XReal<double> >      :: VAR = Numeric<double> :: VAR; \
template <> const TYPE Numeric< XReal<long double> > :: VAR = Numeric<long double> :: VAR

        Y_MKL_DECL_TYPE(unsigned,MANT_DIG);
#if 0
        template <> const unsigned Numeric<float>       :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Numeric<double>      :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;
        template <> const unsigned Numeric<long double> :: MANT_DIG32 = MANT_DIG < 32 ? MANT_DIG : 32;

        namespace
        {
            template <typename T, unsigned M32> struct GetDENOM32
            {
                static const uint32_t ONE   = 1;
                static const uint32_t DEN32 = ONE << M32;

                static const T Value() noexcept
                {
                    static const T _ = DEN32;
                    return _;

                }
            };

            template <typename T> struct GetDENOM32<T,32>
            {
                static const T Value() noexcept { return 4294967296; }
            };
        }

        template <> const float       Numeric<float>       :: DENOM32 = GetDENOM32<float,MANT_DIG32>::Value();
        template <> const double      Numeric<double>      :: DENOM32 = GetDENOM32<double,MANT_DIG32>::Value();
        template <> const long double Numeric<long double> :: DENOM32 = GetDENOM32<long double,MANT_DIG32>::Value();
#endif



        Y_MKL_DECL_TYPE(unsigned,DIG);

        Y_MKL_DECL_TYPE(int,MIN_EXP);
        Y_MKL_DECL_TYPE(int,MAX_EXP);
        Y_MKL_DECL_TYPE(int,MIN_10_EXP);
        Y_MKL_DECL_TYPE(int,MAX_10_EXP);


#define Y_MKL_DECL_REAL(VAR) \
template <> const float              Numeric<float>                :: VAR = FLT_##VAR; \
template <> const double             Numeric<double>               :: VAR = DBL_##VAR; \
template <> const long double        Numeric<long double>          :: VAR = LDBL_##VAR

#define Y_MKL_DECL_XREAL(VAR) \
template <> const XReal<float>       Numeric< XReal<float> >       :: VAR = Numeric<float>::VAR; \
template <> const XReal<double>      Numeric< XReal<double> >      :: VAR = Numeric<double>::VAR; \
template <> const XReal<long double> Numeric< XReal<long double> > :: VAR = Numeric<long double>::VAR

#define Y_MKL_DECL_BOTH(VAR) \
Y_MKL_DECL_REAL(VAR);        \
Y_MKL_DECL_XREAL(VAR)

        Y_MKL_DECL_BOTH(EPSILON);
        Y_MKL_DECL_BOTH(MIN);
        Y_MKL_DECL_BOTH(MAX);
        



        template <> const float       Numeric<float>       :: FTOL = powf( 10.0f,-int(DIG));
        template <> const double      Numeric<double>      :: FTOL = pow(  10.0, -int(DIG));
        template <> const long double Numeric<long double> :: FTOL = powl( 10.0l,-int(DIG));

        template <> const float       Numeric<float>       :: SQRT_EPSILON = sqrtf(FLT_EPSILON);
        template <> const double      Numeric<double>      :: SQRT_EPSILON = sqrt(DBL_EPSILON);
        template <> const long double Numeric<long double> :: SQRT_EPSILON = sqrtl(LDBL_EPSILON);

        Y_MKL_DECL_XREAL(PI);
        Y_MKL_DECL_XREAL(FTOL);
        Y_MKL_DECL_XREAL(SQRT_EPSILON);

        template <> const float       Numeric<float>       :: GOLDEN = (1.0f+sqrtf(5.0f))/2.0f;
        template <> const double      Numeric<double>      :: GOLDEN = (1.0+sqrt(5.0))/2.0;
        template <> const long double Numeric<long double> :: GOLDEN = (1.0l+sqrtl(5.0l))/2.0l;

        template <> const float       Numeric<float>       :: INV_GOLDEN = (-1.0f+sqrtf(5.0f))/2.0f;
        template <> const double      Numeric<double>      :: INV_GOLDEN = (-1.0+sqrt(5.0))/2.0;
        template <> const long double Numeric<long double> :: INV_GOLDEN = (-1.0l+sqrtl(5.0l))/2.0l;

        Y_MKL_DECL_XREAL(GOLDEN);
        Y_MKL_DECL_XREAL(INV_GOLDEN);


        template <> const float       Numeric<float>       :: THETA = std::pow( 10.0f, 1.0f + std::ceil( std::log10( FLT_MIN/FTOL)));
        template <> const double      Numeric<double>      :: THETA = std::pow( 10.0,  1.0  + std::ceil( std::log10(  DBL_MIN/FTOL)));
        template <> const long double Numeric<long double> :: THETA = std::pow( 10.0l, 1.0l + std::ceil( std::log10( LDBL_MIN/FTOL)));

        Y_MKL_DECL_XREAL(THETA);


    }

}

