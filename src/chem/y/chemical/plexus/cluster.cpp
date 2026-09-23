
#include "y/chemical/plexus/cluster.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Cluster:: ~Cluster() noexcept
        {

        }

        Topology & Cluster:: _topo() noexcept
        {
            return *this;
        }



        Cluster:: Cluster(XML::Log     & xml,
                          const EGroup & grp,
                          Equilibria   & eqs,
                          XWritable    & tlK) :
        Object(),
        Topology(xml,grp),
        Conservations(xml,_topo()),
        Combinatorics(xml,_topo(),eqs,tlK),
        canons(xml,laws,_topo(),lfmt),
        next(0),
        prev(0),
        gvid(0)
        {

        }

        void Cluster:: displayState(std::ostream &os, const XReadable &C, const Level L, const XReadable &K) const
        {
            XMul          xmul;
            XAdd          xadd;
            for(const ENode *en=elist->head;en;en=en->next)
            {
                const Equilibrium &eq = **en;
                const xreal_t      eK = eq(K,TopLevel);
                //efmt.print(os << "\t@",**en,false,t0);
                efmt.efmt.print(os << "\t@",eq);
                //os << "'" << std::setw(22) << eK.str() << "'";
                if(true)
                {
                    const xreal_t ma = eq.massAction(eK,xmul,C,L);
                    os << " | ma=" << std::setw(22) << ma.str();
                }
                if( eq.reac.active(C,L) && eq.prod.active(C,L) )
                {
                    const xreal_t A = eq.affinity( eK.log(), xadd, C, L);
                    os << " | A=" << A.str();
                }
                else
                {
                    os << " | [blocked]";
                }
                os << std::endl;
            }
            
        }

    }

}

#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"
#include "y/chemical/weasel.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        OutputStream & Cluster:: viz(OutputStream &fp, const size_t order) const
        {
            const Weasel &weasel = Weasel::Instance();

            assert( order >= 1 );
            assert( order <= grade.size() );


            fp("subgraph cluster_%s {\n",Decimal(gvid).c_str());

            // write all species
            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species &    sp    = **sn;
                const String       color = weasel.getColorFor(sp,SubLevel);
                const char *       style = 0;
                if(unbounded->book.query(sp))
                {
                    style="dashed";
                }
                sp.viz(fp,color.c_str(),style);
            }

            // write equilibria
            for(const ENode *en= grade[order]->head;en;en=en->next)
            {
                const Components &eq   = **en;
                const String     color = weasel.getColorFor(eq,SubLevel);
                eq.vizSelf(fp,color.c_str(),0);
                eq.vizLink(fp,color.c_str());
            }

            // write conservations
            if(1==order)
            {
                size_t ci = 0;
                for(const Conservation::Law *law = laws.head;law;law=law->next)
                {
                    const String color = weasel.getColorFor(ci++);
                    law->viz(fp,color.c_str());
                }
            }

            fp("}\n");
            return fp;
        }


    }

}
