//! \file

#ifndef Y_MKL_Fabs_Included
#define Y_MKL_Fabs_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/type/traits.hpp"
#include "y/int-to-type.hpp"
#include "y/type/alternative.hpp"
#include "y/calculus/iabs.hpp"
#include <cmath>

namespace Yttrium
{

    namespace MKL
    {

        namespace Kernel
        {

            struct Fabs
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
                T Of(const IntegralAPI &, const T x) noexcept { return IAbs(x); }

                template <typename T> static inline
                T Of(const FloatingAPI &, const T x) noexcept { return std::fabs(x); }

                template <typename T> static inline
                typename ScalarFor<T>::Type Of(const MustCallAPI &, const T &x)
                {
                    return x.abs();
                }

            };

        }

        template <typename T> inline
        typename ScalarFor<T>::Type Fabs(typename TypeTraits<T>::ParamType x) {
            static const typename Kernel::Fabs::Selected<T>::API api = {};
            return Kernel::Fabs::Of(api,x);
        }
        
    }

}

#endif // !Y_MKL_Fabs_Included
