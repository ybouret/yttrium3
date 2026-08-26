
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Clusters:: ~Clusters() noexcept
        {
        }

        Clusters:: Clusters(XML::Log   & xml,
                            Equilibria & eqs) :
        Proxy<const Core::ListOf<Cluster> >(),
        list(),
        topK()
        {
            const size_t numEqs = eqs->size();
            Y_XML_Element_Attr(xml,BuildClusters,Y_XML_Attr(numEqs));

            // create partition
            const Partition part(xml,eqs);

            // create one cluster per detected group
            for(const EGroup *g=part.party.head;g;g=g->next)
            {
                list.pushTail( new Cluster(xml,*g,eqs,topK) );
            }

            // prepare top level K
            topK.adjust(eqs->size(),0);
        }

        Y_Proxy_Impl(Clusters,list)

    }

}
