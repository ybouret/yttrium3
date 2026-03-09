//! \file

#ifndef Y_Core_Shuffle_Included
#define Y_Core_Shuffle_Included 1

#include "y/swap.hpp"

namespace Yttrium
{
    namespace Core
    {
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

#endif // !Y_Core_Shuffle_Included

