
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Clusters:: ~Clusters() noexcept
        {
        }

        Clusters:: Clusters(XML::Log   & xml,
                            Equilibria & eqs)
        {
            const Partition part(xml,eqs);
            for(const EGroup *g=part.party.head;g;g=g->next)
            {
                list.pushTail( new Cluster(xml,*g) );
            }
        }

        Y_Proxy_Impl(Clusters,list)

    }

}
