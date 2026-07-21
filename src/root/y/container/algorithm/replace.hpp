

//! \file

#ifndef Y_Algorithm_Replace_Included
#define Y_Algorithm_Replace_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    namespace Algorithm
    {

        template <typename ITERATOR, typename SOURCE, typename TARGET>
        static inline
        void Replace(ITERATOR curr, size_t size, SOURCE &source, TARGET &target)
        {
            while(size-- > 0)
            {
                if(source == *curr) *curr = target;
                ++curr;
            }
        }

        template <typename SEQUENCE, typename SOURCE, typename TARGET>
        static inline void Replace(SEQUENCE &seq, SOURCE &source, TARGET &target)
        {
            Replace(seq.begin(),seq.size(),source,target);
        }

    }
}

#endif // !Y_Algorithm_Replace_Included


