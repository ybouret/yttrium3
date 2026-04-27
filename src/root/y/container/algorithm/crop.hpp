
//! \file

#ifndef Y_Algorithm_Crop_Included
#define Y_Algorithm_Crop_Included 1

#include "y/container/algorithm/trim.hpp"
#include "y/container/algorithm/skip.hpp"


namespace Yttrium
{
    namespace Algorithm
    {
        //! Crop bad items
        /**
         \param seq   sequence-like container
         \param isBad illness detector
         \return trimmed and skipped sequence
         */
        template <typename SEQUENCE, typename IS_BAD> inline
        SEQUENCE Crop(SEQUENCE &seq, IS_BAD &isBad) noexcept
        {
            return Trim(seq,isBad).Skip(seq.isBad);
        }
    }
}

#endif // !Y_Algorithm_Crop_Included


