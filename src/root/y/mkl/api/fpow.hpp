//! \file

#ifndef Y_MKL_FPow_Included
#define Y_MKL_FPow_Included 1

#include "y/mkl/xreal.hpp"
#include "y/type/alternative.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            struct Fpow
            {
                enum Kind
                {
                    NativeFP,
                    Extended,
                    Rejected
                };

                typedef TL3(XReal<float>, XReal<double>, XReal<long double>) XReals;

                typedef IntToType<NativeFP> UseNativeFP;
                typedef IntToType<Extended> UseExtended;
                typedef IntToType<Rejected> InvalidType;

                template <typename T> struct Selected
                {
                    static const bool IsNativeFP = TypeTraits<T>::IsIsoFloatingPoint;
                    static const bool IsExtended = ( TL::IndexOf<XReals,T>::Value >= 0 );
                    typedef typename Alternative<IsNativeFP,UseNativeFP,IsExtended,UseExtended,InvalidType>::Type API;
                };

                template <typename T> static inline
                T Of(const UseNativeFP &, const T &x, const T &a)
                {
                    return std::pow(x,a);
                }

                template <typename T> static inline
                T Of(const UseExtended &, const T &x, const T &a)
                {
                    return x.pow(a);
                }
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        }


        //! \param x value \param a exponent \return x^a
        template <typename T> inline
        T Fpow(const T x, const T a)
        {
            static const typename Kernel::Fpow::Selected<T>::API api = {};
            return Kernel::Fpow::Of<T>(api,x,a);
        }

    }

}

#endif // !Y_MKL_FPow_Included

