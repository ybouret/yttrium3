
//! \file

#ifndef Y_Core_Find_Included
#define Y_Core_Find_Included 1

#include <cstdlib>

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //! linear lookup of data in a range
        /**
         \param lhs  argument to find
         \param iter first iterator
         \param size number of elements
         \return true iff one of the elements is equal to lhs
         */
        //______________________________________________________________________
        template <typename ITER, typename LHS> inline
        bool Find(LHS &lhs, ITER iter, size_t size)
        {
            while(size-- > 0) {
                if( lhs == *iter ) return true;
                ++iter;
            }
            return false;
        }

    }
}

#endif // !Y_Core_Find_Included

