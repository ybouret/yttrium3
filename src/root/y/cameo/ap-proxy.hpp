//! \file

#ifndef Y_Cameo_AP_Proxy_Included
#define Y_Cameo_AP_Proxy_Included 1


#include "y/type/traits.hpp"
#include "y/apex/integer.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        //! compute parameters for given type
        template <typename T> struct UseAP_ProxyAPI
        {
            static const bool UseSigned   = TypeTraits<T>::InStandardIntegers || TypeTraits<T>::InPlatformIntegers; //!< alias
            static const bool UseUnsigned = TypeTraits<T>::InStandardUnsigned || TypeTraits<T>::InPlatformUnsigned; //!< alias
            typedef typename Alternative<UseSigned,apz,UseUnsigned,apz,NullType>::Type Type;                        //!< alias
        };

        //! common stuff for AP_Proxy
        class AP_ProxyCommon
        {
        public:
            static const char * const VarName; //!< for cast
            static const char * const VarPart; //!< for cast

            explicit AP_ProxyCommon() noexcept; //!< setup
            virtual ~AP_ProxyCommon() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(AP_ProxyCommon); //!< discarded
        };

    }
}

#endif // !Y_Cameo_AP_Proxy_Included
