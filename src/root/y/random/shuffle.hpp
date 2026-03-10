//! \file

#ifndef Y_Random_Shuffle_Included
#define Y_Random_Shuffle_Included 1

#include "y/swap.hpp"

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //! Fisher-Yates shuffle of a range
        /**
         \param ran posseses a leq<size_t>(size_t) method
         \param a   first iterator
         \param n   number of items to shuffle
         */
        //______________________________________________________________________
        template <typename RAND, typename ITER> inline
        void Shuffle(RAND &ran, ITER a, const size_t n) noexcept
        {
            for(size_t i=n-1;i>0;--i)
            {
                const size_t j = ran.template leq<size_t>(i);
                BSwap(a[i],a[j]);
            }
        }

    }
}

#endif // !Y_Random_Shuffle_Included

