
#include "y/chemical/plexus/clusters.hpp"
#include "y/core/max.hpp"

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
        K(topK),
        maxGrade(0),
        part(xml,eqs)
        {

            const size_t initialCount = eqs->size();
            Y_XML_Element_Attr(xml,BuildClusters,Y_XML_Attr(initialCount));

            //__________________________________________________________________
            //
            // create one cluster per detected group
            //__________________________________________________________________
            {
                unsigned gvid = 0;
                for(const EGroup *g=part.party.head;g;g=g->next)
                {
                    Cluster * const cl =list.pushTail( new Cluster(xml,*g,eqs,topK) );
                    Coerce(cl->gvid) = gvid++;
                    InSituMax(Coerce(maxGrade),cl->grade.size());
                }
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
            if(xml.verbose)
            {
                const size_t finalCount = eqs->size();
                Y_XML_Element_Attr(xml,DisplayInitial,Y_XML_Attr(finalCount) << Y_XML_Attr(initialCount));
                {
                    for(const Cluster *cl=list.head;cl;cl=cl->next)
                    {
                        const size_t GraphVizID = cl->gvid;
                        Y_XML_Element_Attr(xml,Cluster, Y_XML_Attr(GraphVizID) );
                        for(const ENode *en=cl->elist->head;en;en=en->next)
                        {
                            eqs.EqFormat::print(xml() << "@ ",**en,true,t0);
                        }
                        Y_XMLog(xml, "|_species=" << cl->slist);
                    }
                }
            }


        }

        void Clusters:: update(const xreal_t t)
        {
            for(Cluster *cl=list.head;cl;cl=cl->next)
            {
                for(ENode *en=cl->elist->head;en;en=en->next)
                {
                    Equilibrium &eq = **en;
                    eq(topK,TopLevel) = eq.K(t);
                }
            }
        }

    }

}
