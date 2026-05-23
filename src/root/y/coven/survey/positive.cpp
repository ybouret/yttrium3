
#include "y/coven/survey/positive.hpp"

namespace Yttrium
{

    namespace Coven
    {
        PositiveSurvey::  PositiveSurvey(const size_t nmin) noexcept :
        Survey(nmin)
        {
        }

        PositiveSurvey:: ~PositiveSurvey() noexcept
        {
        }

        bool PositiveSurvey:: takes(const Vector &v) const noexcept
        {
            assert(v.ncof>0);
            return v.nneg <= 0;
        }


    }

}

