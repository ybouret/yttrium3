

//! \file

#ifndef Y_Algorithm_Equality_Included
#define Y_Algorithm_Equality_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    namespace Algorithm
    {
        template <typename L_ITER, typename R_ITER> static inline
        bool AreEqualRanges(L_ITER l, const size_t n, R_ITER r, const size_t m)
        {
            if(n!=m) return false;
            for(size_t i=n;i>0;--i)
            {
                if( *(l++) != *(r++) ) return false;
            }
            return true;
        }

        template <typename LHS, typename RHS> static inline
        bool AreEqualSequences(LHS &lhs, RHS &rhs)
        {
            return AreEqualRanges(lhs.begin(),lhs.size(),rhs.begin(),rhs.size());
        }


    }
}

#endif // !Y_Algorithm_Equality_Included


