

#include "y/chemical/reactive/equilibrium/constant.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        ConstantEquilibrium:: ~ConstantEquilibrium() noexcept
        {
        }

        ConstantEquilibrium:: ConstantEquilibrium(const String &eqName, const size_t eqIndx, const xreal_t eqK) :
        Equilibrium(eqName,eqIndx),
        K_(eqK)
        {
        }

        xreal_t ConstantEquilibrium:: getK(xreal_t)
        {
            return K_;
        }

    }

}

