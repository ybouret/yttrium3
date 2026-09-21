
#include "y/chemical/plexus/solvers.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Solvers:: ~Solvers() noexcept
        {
        }

        Y_Proxy_Impl(Solvers,solvers)


        Solvers:: Solvers(const Clusters &clusters) :
        Proxy<const Core::ListOf<Solver>>(),
        solvers()
        {
            for(const Cluster *cls=clusters->head;cls;cls=cls->next)
            {
                solvers.pushTail( new Solver(*cls) );
            }
        }


    }

}
