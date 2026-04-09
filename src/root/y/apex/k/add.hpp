
//! \file

#ifndef Y_Apex_KegAdd_Included
#define Y_Apex_KegAdd_Included 1

#include "y/apex/k/keg.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Apex
    {


        template <typename WORD, typename CORE> inline
        Keg<WORD> * KegAdd(const WORD * const lhs,
                           const size_t       nlw,
                           const WORD * const rhs,
                           const size_t       nrw)
        {
            Y_STATIC_CHECK(sizeof(WORD)<sizeof(CORE),BadSizes);
            
        }


    }

}

#endif // !Y_Apex_KegAdd_Included

