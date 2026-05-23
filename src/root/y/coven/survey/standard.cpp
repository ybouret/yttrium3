#include "y/coven/survey/standard.hpp"

namespace Yttrium
{

    namespace Coven
    {
        StandardSurvey:: StandardSurvey(const size_t nmin) noexcept :
        Survey(nmin)
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

