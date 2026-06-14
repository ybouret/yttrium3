

#include "y/chemical/reactive/equilibria.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Equilibria:: ~Equilibria() noexcept
        {
        }

        Y_Proxy_Impl(Equilibria,db)
        
        Equilibria:: Equilibria() :
        Proxy<const EqSet>(),
        db()
        {}

        Equilibria:: Equilibria(const Equilibria &eqs) :
        Proxy<const EqSet>(),
        db(eqs.db)
        {}

    }

}
