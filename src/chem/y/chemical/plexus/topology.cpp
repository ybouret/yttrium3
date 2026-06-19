
#include "y/chemical/plexus/topology.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Topology:: ~Topology() noexcept
        {
        }


        static inline
        void fillSList(SList &slist, const Actors &actors)
        {
            for(const Actor *ac=actors->head;ac;ac=ac->next)
            {
                const Species &sp = ac->sp;
                if(!slist.found(sp)) slist << sp;
            }
        }

        static inline
        void fillSList(SList &slist, const Components &eq)
        {
            fillSList(slist,eq.reac);
            fillSList(slist,eq.prod);
            Indexed::SubLabel(Indexed::TopHSort(slist));
        }

        Topology:: Topology(XML::Log &xml,const EList &g) :
        group(g),
        elist(group),
        slist(),
        nu(),
        nuT(),
        N(nu.rows),
        M(nu.cols),
        efmt(),
        sfmt()
        {
            Y_XML_Element_Attr(xml,BuildTopology,Y_XML_Attr(group->size));
            for(const ENode *en=elist->head;en;en=en->next)
            {
                const Equilibrium &eq = **en;
                fillSList( Coerce(slist), eq) ;
                Coerce(efmt).enroll(eq);
            }
            Y_XMLog(xml, "species=" << slist);

            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species &sp = **sn;
                Coerce(sfmt).enroll(sp);
            }

            Coerce(nu).make(elist->size,slist->size);
            Y_XMLog(xml, "N = " << std::setw(4) << N << " | M =" << std::setw(4) << M);
            for(const ENode *en=elist->head;en;en=en->next)
            {
                const Components &eq  = **en;
                const size_t      row = eq.indx[SubLevel];
                eq.topology( Coerce(nu[row]),SubLevel);;
            }
            Y_XMLog(xml, "nu=" << nu);

            const size_t rank = MKL::Rank::Of(nu);
            if(N!=rank) throw Specific::Exception("Topology","dependent equilibria detected!");
            Coerce(nuT).make(M,N).assignTranspose(nu);
        }



    }

}
