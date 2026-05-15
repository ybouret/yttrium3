
//! \file

#ifndef Y_Cameo_AP_Proxy_Included
#define Y_Cameo_AP_Proxy_Included 1


#include "y/type/traits.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Pith
        {
            enum AP_Proxy_Type
            {
                AP_Proxy_Signed,
                AP_Proxy_Unsigned,
                AP_Proxy_Rejected
            };

            template <AP_Proxy_Type> struct AP_Proxy_Info;

            template<> struct AP_Proxy_Info<AP_Proxy_Signed>
            {
                typedef apz Type;
            };

            template<> struct AP_Proxy_Info<AP_Proxy_Unsigned>
            {
                typedef apn Type;
            };

        }
        
        template <typename T> struct UseAP_ProxyAPI
        {

        };
    }
}

#endif // !Y_Cameo_AP_Proxy_Included
