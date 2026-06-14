
#include "y/chemical/reactive/equilibrium.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Equilibrium:: CallSign = "Equilibrium";
        const char * const Equilibrium:: Symbol = "<=>";

        Equilibrium:: ~Equilibrium() noexcept
        {
        }

        Equilibrium:: Equilibrium(const String &eqName, const size_t eqIndx) :
        Components(eqName,eqIndx)
        {
        }

        xreal_t Equilibrium:: K(xreal_t t)
        {
            const xreal_t k = getK(t);
            if(k<=0.0) throw Specific::Exception(name.c_str(),"negative K @time=%g", (double) k);
            return k;
        }

    }

}

