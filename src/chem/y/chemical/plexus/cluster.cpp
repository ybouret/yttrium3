
#include "y/chemical/plexus/cluster.hpp"
#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Cluster:: ~Cluster() noexcept
        {
            
        }

        Cluster:: Cluster(XML::Log     & xml,
                          const EGroup & grp,
                          Equilibria   & eqs,
                          XWritable    & tlK) :
        topology(xml,grp),
        conservations(xml,topology),
        canons(xml,conservations.laws,topology,conservations.lfmt),
        combinatorics(xml,Coerce(topology),eqs,tlK),
        next(0),
        prev(0),
        gvid(0)
        {

        }


        OutputStream & Cluster:: viz(OutputStream &fp, const size_t order) const
        {
            assert( order >= 1 );
            assert( order <= combinatorics.grade.size() );

            fp("subgraph cluster_%s {\n",Decimal(gvid).c_str());

            // write all species
            for(const SNode *sn=topology.slist->head;sn;sn=sn->next)
            {
                (**sn).viz(fp,0,0);
            }

            // write equilibria
            const EList &elist = combinatorics.grade[order];
            for(const ENode *en=elist->head;en;en=en->next)
            {
                const Components &eq = **en;
                eq.vizSelf(fp,0,0);
                eq.vizLink(fp,0);
            }

            fp("}\n");
            return fp;
        }


    }

}
