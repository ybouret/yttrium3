

//! \file

#ifndef Y_Cameo_Straight_Included
#define Y_Cameo_Straight_Included 1


#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //! compute parameters for given SCALART type
        template <typename T>
        struct UseStraightAPI
        {
            static const bool IsProper = Y_Is_SuperSubClass_Strict(Apex::Number,T); //!< alias
        };
    }
}

#endif // !Y_Cameo_Straight_Included
