//! \file

#ifndef Y_Cameo_API_Included
#define Y_Cameo_API_Included 1

#include "y/type/traits.hpp"
#include "y/int-to-type.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //! scalar type strategy
        enum Strategy
        {
            Straight, //!< for Apex::Number
            FP_Queue, //!< for floating point
            AP_Proxy  //!< for integer type using apex
        };

        typedef IntToType<Straight> StraightAPI;
        typedef IntToType<FP_Queue> FP_QueueAPI;
        typedef IntToType<AP_Proxy> AP_ProxyAPI;


        

    }
}

#endif // !Y_Cameo_API_Included

