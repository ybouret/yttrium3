//! \file

#ifndef Y_Algorithm_Trim_Included
#define Y_Algorithm_Trim_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    namespace Algorithm
    {
        //! Trim bad items
        /**
         \param seq   sequence-like container
         \param isBad illness detector
         \return trimmed sequence
         */
        template <typename SEQUENCE, typename IS_BAD> inline
        SEQUENCE Trim(SEQUENCE &seq, IS_BAD &isBad) noexcept
        {
            while(seq.size() && isBad( seq.tail() ) )
                seq.popTail();
            return seq;
        }
    }
}

#endif // !Y_Algorithm_Trim_Included


