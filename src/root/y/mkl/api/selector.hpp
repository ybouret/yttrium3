
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

        }




    }

}

#endif // !Y_MKL_API_Selector_Included
