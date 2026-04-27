
//! \file

#ifndef Y_Algorithm_Skip_Included
#define Y_Algorithm_Skip_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    namespace Algorithm
    {
        //! Skip bad items
        /**
         \param seq   sequence-like container
         \param isBad illness detector
         \return skipped sequence
         */
        template <typename SEQUENCE, typename IS_BAD> inline
        SEQUENCE Skip(SEQUENCE &seq, IS_BAD &isBad) noexcept
        {
            while(seq.size() && isBad( seq.head() ) )
                seq.popHead();
            return seq;
        }
    }
}

#endif // !Y_Algorithm_Skip_Included


