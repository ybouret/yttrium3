
//! \file

#ifndef Y_Cameo_Sum_Raised_API
#define Y_Cameo_Sum_Raised_API 1


#include "y/apex/integer.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {
            //! compute raised parameters for given type
            template <typename T> struct ByRaisedAPI
            {
                static const bool UseSigned   = TypeTraits<T>::InStandardIntegers || TypeTraits<T>::InPlatformIntegers; //!< alias
                static const bool UseUnsigned = TypeTraits<T>::InStandardUnsigned || TypeTraits<T>::InPlatformUnsigned; //!< alias
                static const bool IsProper    =  UseSigned || UseUnsigned;                                              //!< acceptable
                typedef typename Alternative<UseSigned,apz,UseUnsigned,apn,NullType>::Type Type;                        //!< alias
            };

            //! helper for static check
#define Y_Cameo_Sum_Raised_Check() Y_STATIC_CHECK(ByRaisedAPI<MutableType>::IsProper,BadType)

        }
    }
}

#endif // !Y_Cameo_Sum_Raised_API
