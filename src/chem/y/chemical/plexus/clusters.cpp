
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Clusters:: ~Clusters() noexcept
        {
        }

        Y_Proxy_Impl(Clusters,list)

        Clusters:: Clusters(XML::Log   & xml,
                            Equilibria & eqs) :
        Proxy<const Core::ListOf<Cluster> >(),
        list(),
        topK()
        {
            const size_t numEqs = eqs->size();
            Y_XML_Element_Attr(xml,BuildClusters,Y_XML_Attr(numEqs));

            //__________________________________________________________________
            //
            // create partition
            //__________________________________________________________________
            const Partition part(xml,eqs);

            //__________________________________________________________________
            //
            // create one cluster per detected group
            //__________________________________________________________________
            for(const EGroup *g=part.party.head;g;g=g->next)
                list.pushTail( new Cluster(xml,*g,eqs,topK) );
            

            //__________________________________________________________________
            //
            // prepare top level K
            //__________________________________________________________________
            topK.adjust(eqs->size(),0);
        }

        const XReadable & Clusters:: K(const xreal_t t)
        {
            for(Cluster *cl=list.head;cl;cl=cl->next)
            {
                for(ENode *en=cl->topology.elist->head;en;en=en->next)
                {
                    Equilibrium &eq = **en;
                    eq(topK,TopLevel) = eq.K(t);
                }
            }
            return topK;
        }

    }

}
