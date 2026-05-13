
//! \file

#ifndef Y_MKL_Sqrt_Included
#define Y_MKL_Sqrt_Included 1

#include "y/type/traits.hpp"
#include "y/int-to-type.hpp"
#include "y/type/alternative.hpp"
#include "y/calculus/isqrt.hpp"
#include <cmath>

namespace Yttrium
{

    namespace MKL
    {

        namespace Kernel
        {

            struct Sqrt
            {
                enum Genus
                {
                    Integral,
                    Floating,
                    MustCall
                };

                typedef IntToType<Integral> IntegralAPI;
                typedef IntToType<Floating> FloatingAPI;
                typedef IntToType<MustCall> MustCallAPI;

                template <typename T> struct Selected
                {
                    static const bool UseIntegral = TypeTraits<T>::IsIntegral;
                    static const bool UseFloating = TypeTraits<T>::IsIsoFloatingPoint;
                    typedef typename Alternative<UseIntegral,IntegralAPI,UseFloating,FloatingAPI,MustCallAPI>::Type API;
                };

                template <typename T> static inline
                T Of(const IntegralAPI &, const T x) noexcept { return IntegerSquareRoot(x); }

                template <typename T> static inline
                T Of(const FloatingAPI &, const T x) noexcept { return std::sqrt(x); }

                template <typename T> static inline
                T Of(const MustCallAPI &, const T &x)
                {
                    return x.sqrt();
                }

            };

        }

        template <typename T> inline
        T Sqrt(typename TypeTraits<T>::ParamType x) {
            static const typename Kernel::Sqrt::Selected<T>::API api = {};
            return Kernel::Sqrt::Of(api,x);
        }

    }

}

#endif // !Y_MKL_Sqrt_Included
