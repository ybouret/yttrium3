
//! \file

#ifndef Y_MKL_API_Selector_Included
#define Y_MKL_API_Selector_Included 1

#include "y/type/traits.hpp"
#include "y/int-to-type.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Kernel
        {
            //! named API to use
            enum Genus
            {
                Integral, //!< use Iabs
                Floating, //!< use std::fabs
                MustCall  //!< use .abs()
            };

            typedef IntToType<Integral> IntegralAPI; //!< alias
            typedef IntToType<Floating> FloatingAPI; //!< alias
            typedef IntToType<MustCall> MustCallAPI; //!< alias

            //! API Selector
            template <typename T> struct Selected
            {
                static const bool UseIntegral = TypeTraits<T>::IsIntegral;         //!< alias
                static const bool UseFloating = TypeTraits<T>::IsIsoFloatingPoint; //!< alias
                typedef typename Alternative<UseIntegral,IntegralAPI,UseFloating,FloatingAPI,MustCallAPI>::Type API; //!< the API
            };

        }




    }

}

#endif // !Y_MKL_API_Selector_Included
