#include "y/chemical/plexus/conservations.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/exception.hpp"

#include "y/coven/survey/positive.hpp"
#include "y/coven/survey/inquiry.hpp"
#include "y/ascii/plural.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Conservations:: ~Conservations() noexcept
        {
        }

        Conservations:: Conservations(XML::Log       &xml,
                                      const Topology &topo) :
        Qm(),
        Nc(Qm.rows),
        rg(0),
        laws(),
        conserved( new SpRoll() ),
        unbounded( new SpRoll() )
        {
            Y_XML_Element(xml,BuildConservations);
            Matrix<apz> Q;
            if( ! MKL::OrthoSpace::Get(Q,topo.nu) )
            {
                Y_XMLog(xml, "no orthogonal space");
                collectSpecies(xml,topo.slist);
            }
            else
            {
                Y_XMLog(xml,"Q=" << Q);
                Coven::Inquiry<Coven::PositiveSurvey> survey(Q,2,Coven::Tribes::Optimizing);
                const size_t nc = (**survey).size;
                if(!nc)
                {
                    Y_XMLog(xml, "|_no conservation");
                    collectSpecies(xml,topo.slist);
                }
                else
                {
                    Y_XMLog(xml,"|_[ -- found " << nc << " conservation" << ASCII::Plural::s(nc) << " --]" );
                    {
                        const size_t M   = topo.M;
                        UMatrix &    A   = Coerce(Qm).make(nc,M);
                        size_t       i   = 1;
                        for(const Coven::Vector *v=(**survey).head;v;v=v->next,++i)
                        {
                            Law * const       law =  Coerce(laws).pushTail( new Law(i) );
                            UMatrix::RowType &Ai  = A[i];
                            {
                                const Coven::Vector &V  = *v;
                                const SNode         *sn = topo.slist->head;
                                for(size_t j=1;j<=M;++j,sn=sn->next)
                                {
                                    unsigned &nu = Ai[j];
                                    if(!V[j].tryCast(nu))
                                        throw Specific::Exception("Canon","invalid coefficient[%u][%u]",(unsigned)i,(unsigned)j);
                                    if(nu>0)
                                        law->hire(nu,**sn);
                                }
                            }
                            Y_XMLog(xml, "|_0=" << *law );
                            assert((*law)->size>=2);
                        }
                    }

                    // compute Rank
                    Coerce(rg) = MKL::Rank::Of(Qm);
                    Y_XMLog(xml, "Qm  = " << Qm);
                    Y_XMLog(xml, "nuT = " << topo.nuT);
                    Y_XMLog(xml, "Nc  = " << Nc);
                    Y_XMLog(xml, "rg  = " << rg);

                    // collect species
                    collectSpecies(xml,topo.slist);



                }
            }
        }

        void Conservations:: collectSpecies(XML::Log &xml, const SList &slist)
        {
            // collect conserved species
            for(const Law *law=laws.head;law;law=law->next)
            {
                for(const Actor *ac=(*law)->head;ac;ac=ac->next)
                {
                    Coerce(*conserved).inscribe(ac->sp);
                }
            }

            // deduce unbounded species
            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species &sp = **sn;
                if(conserved->book.query(sp)) continue;
                Coerce(*unbounded).inscribe(sp);
            }

            Y_XMLog(xml, "conserved = " << conserved->list);
            Y_XMLog(xml, "unbounded = " << unbounded->list);
        }



    }

}

