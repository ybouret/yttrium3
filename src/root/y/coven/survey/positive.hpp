

//! \file

#ifndef Y_Coven_PositiveSurvey_Included
#define Y_Coven_PositiveSurvey_Included 1

#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Survey of at only (at least 1) positive, or zero coefficients
        //
        //
        //______________________________________________________________________
        class PositiveSurvey : public Survey
        {
        public:
            explicit PositiveSurvey(const size_t) noexcept; //!< setup
            virtual ~PositiveSurvey() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(PositiveSurvey); //!< discarded
            virtual bool takes(const Vector &) const noexcept;
        };
    }

}

#endif // !Y_Coven_PositiveSurvey_Included

