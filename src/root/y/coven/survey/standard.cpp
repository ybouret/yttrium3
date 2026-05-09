#include "y/coven/survey/standard.hpp"

namespace Yttrium
{

    namespace Coven
    {
        StandardSurvey:: StandardSurvey() noexcept
        {
        }

        StandardSurvey:: ~StandardSurvey() noexcept
        {
        }

        bool StandardSurvey:: takes(const Vector &) const noexcept
        {
            return true;
        }


    }

}

