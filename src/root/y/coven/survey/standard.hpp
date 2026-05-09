
//! \file

#ifndef Y_Coven_StandardSurvey_Included
#define Y_Coven_StandardSurvey_Included 1

#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Survey of at least one negative or positive coefficients
        //
        //
        //______________________________________________________________________
        class StandardSurvey : public Survey
        {
        public:
            explicit StandardSurvey() noexcept; //!< setup
            virtual ~StandardSurvey() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(StandardSurvey); //!< discarded
            virtual bool takes(const Vector &) const noexcept;
        };
    }

}

#endif // !Y_Coven_StandardSurvey_Included

