
#include "y/chemical/plexus/combinatorics.hpp"
#include "y/container/cxx/series.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Combinatorics:: ~Combinatorics() noexcept
        {
        }


        namespace
        {
            template <typename ARRAY>
            static inline size_t CountNonZeroIn(ARRAY &a)
            {
                size_t count = 0;
                for(size_t i=a.size();i>0;--i) {
                    if( 0 != a[i] ) ++count;
                }
                return count;
            }
        }

        Combinatorics:: Combinatorics(XML::Log   & xml,
                                      Topology   & topo,
                                      Equilibria & eqs)
        {
            Y_XML_Element(xml,BuildCombinatorics);
            const SList   & slist = topo.slist;
            const IMatrix & nuT   =  topo.nuT;
            Y_XMLog(xml, "species = " << slist);
            Y_XMLog(xml, "nuT     = " << nuT);

            SList              msp;
            CxxSeries<size_t>  mid(slist->size);

            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species       & sp = **sn;
                const size_t          sj = sp.indx[SubLevel];
                const Readable<int> & cf = nuT[sj]; if(CountNonZeroIn(cf)<=1) continue;
                msp << sp;
                mid << sj;
            }

            if(msp->size<=0)
            {
                Y_XMLog(xml, "no species in multiple equilbria");
            }
            else
            {
                Y_XMLog(xml, "species = " << slist);
                Y_XMLog(xml, "multi   = " << msp << " @" << mid);
            }


        }
        
    }

}
