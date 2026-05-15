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

        template <typename T> struct UseAP_ProxyAPI
        {
            static const bool UseSigned   = TypeTraits<T>::InStandardIntegers || TypeTraits<T>::InPlatformIntegers;
            static const bool UseUnsigned = TypeTraits<T>::InStandardUnsigned || TypeTraits<T>::InPlatformUnsigned;
            typedef typename Alternative<UseSigned,apz,UseUnsigned,apz,NullType>::Type Type;
        };

        class AP_ProxyCommon
        {
        public:
            static const char * const VarName;
            static const char * const VarPart;
            
            explicit AP_ProxyCommon() noexcept;
            virtual ~AP_ProxyCommon() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(AP_ProxyCommon);
        };

    }
}

#endif // !Y_Cameo_AP_Proxy_Included
