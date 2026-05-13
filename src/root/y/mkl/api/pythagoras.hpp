
//! \file

#ifndef Y_MKL_Pythagoras_Included
#define Y_MKL_Pythagoras_Included 1

#include "y/core/sort3.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/check/static.hpp"
#include <cassert>


namespace Yttrium
{
    namespace MKL
    {

        //! |a^2+b^2|^(1/2) with minimal precision loss
        /**
         \param a first side
         \param b second side
         \return sqrt(a*a+b*b)
         */
        template <typename T> T Pythagoras(const T a, const T b)
        {
            Y_STATIC_CHECK(IsScalar<T>::Value,BadType);
            const T absa = Fabs<T>(a);
            const T absb = Fabs<T>(b);
            const T one(1);
            
            if (absa > absb)
            {
                const T rho  = absb/absa;
                const T arg  = one + rho*rho;
                return absa*Sqrt<T>(arg);
            }
            else
            {
                assert(absa<=absb);
                const T zero(0);
                if( absb <= zero )
                    return zero;
                else
                {
                    const T rho  = absa/absb;
                    const T arg  = one + rho*rho;
                    return absb*Sqrt<T>(arg);
                }
            }
        }

        //! |a^2+b^2+c^2|^(1/2) with minimal precision loss
        /**
         \param a first  side
         \param b second side
         \param c thirds side
         \return sqrt(a*a+b*b+c*c*)
         */
        template <typename T> T Pythagoras(const T a, const T b, const T c)
        {
            Y_STATIC_CHECK(IsScalar<T>::Value,BadType);
            T absv[3] = { Fabs<T>(a), Fabs<T>(b), Fabs<T>(c) };
            Core::Sort3(absv);
            const T zero(0);
            if(absv[2]<=zero) return zero;
            const T one(1);
            const T arg0 = absv[0]/absv[2];
            const T arg1 = absv[1]/absv[2];
            const T sarg = (arg0*arg0+arg1*arg1) + one;
            return absv[2] * Sqrt<T>(sarg);
        }


    }
}

#endif // !Y_MKL_Pythagoras_Included

