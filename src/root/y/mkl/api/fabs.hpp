//! \file

#ifndef Y_MKL_Fabs_Included
#define Y_MKL_Fabs_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/mkl/api/selector.hpp"
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
            static const typename Kernel::Selected<T>::API api = {};
            return Kernel::Fabs::Of(api,x);
        }
        
    }

}

#endif // !Y_MKL_Fabs_Included
