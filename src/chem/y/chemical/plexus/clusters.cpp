
#include "y/chemical/plexus/clusters.hpp"
#include "y/chemical/reactive/equilibrium/partition.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Clusters:: ~Clusters() noexcept
        {
        }

        Y_Proxy_Impl(Clusters,list)

        Clusters:: Clusters(XML::Log   &  xml,
                            Equilibria &  eqs,
                            const xreal_t t0) :
        Proxy<const Core::ListOf<Cluster> >(),
        list(),
        topK(),
        K(topK)
        {

            const size_t initialCount = eqs->size();
            Y_XML_Element_Attr(xml,BuildClusters,Y_XML_Attr(initialCount));

            //__________________________________________________________________
            //
            // create partition
            //__________________________________________________________________
            const Partition part(xml,eqs);

            //__________________________________________________________________
            //
            // create one cluster per detected group
            //__________________________________________________________________
            {
                unsigned gvid = 0;
                for(const EGroup *g=part.party.head;g;g=g->next)
                    Coerce(list.pushTail( new Cluster(xml,*g,eqs,topK) )->gvid) = gvid++;

            }


            //__________________________________________________________________
            //
            // prepare top level K
            //__________________________________________________________________
            topK.adjust(eqs->size(),0);


            //__________________________________________________________________
            //
            // Initialize
            //__________________________________________________________________
            update(t0);
            const size_t finalCount = eqs->size();
            Y_XML_Element_Attr(xml,DisplayInitial,Y_XML_Attr(finalCount) << Y_XML_Attr(initialCount));

            if(xml.verbose)
            {
                for(const Cluster *cl=list.head;cl;cl=cl->next)
                {
                    const unsigned gvid = cl->gvid;
                    Y_XML_Element_Attr(xml,Cluster, Y_XML_Attr(gvid) );
                    for(const ENode *en=cl->topology.elist->head;en;en=en->next)
                    {
                        eqs.EqFormat::print(xml() << "@ ",**en,true,t0);
                    }
                }
            }


        }

        void Clusters:: update(const xreal_t t)
        {
            for(Cluster *cl=list.head;cl;cl=cl->next)
            {
                for(ENode *en=cl->topology.elist->head;en;en=en->next)
                {
                    Equilibrium &eq = **en;
                    eq(topK,TopLevel) = eq.K(t);
                }
            }
        }

    }

}
