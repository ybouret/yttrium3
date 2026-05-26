
//! \file

#ifndef Y_Cameo_Sum_Direct_API
#define Y_Cameo_Sum_Direct_API 1


#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {
            //! compute parameters for given SCALAR type
            template <typename T>
            struct ByDirectAPI
            {
                static const bool IsProper = Y_Is_SuperSubClass_Strict(Apex::Number,T); //!< alias
            };

            //! helper for static check
#define Y_Cameo_Sum_Direct_Check() Y_STATIC_CHECK(ByDirectAPI<MutableType>::IsProper,BadType)
        }

    }

}

#endif // !Y_Cameo_Sum_Direct_API

