#include "y/chemical/plexus/canon.hpp"
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
        Canon:: ~Canon() noexcept
        {
        }

        Canon:: Canon(XML::Log &xml, const Topology &topo) :
        Qm(),
        Nc(Qm.rows),
        rg(0),
        laws()
        {
            Y_XML_Element(xml,BuildCanon);
            Matrix<apz> Q;
            if( ! MKL::OrthoSpace::Get(Q,topo.nu) )
            {
                Y_XMLog(xml, "no orthogonal space");
            }
            else
            {
                Y_XMLog(xml,"Q=" << Q);
                Coven::Inquiry<Coven::PositiveSurvey> survey(Q,2,Coven::Tribes::Optimizing);
                const size_t nc = (**survey).size;
                if(!nc)
                {
                    Y_XMLog(xml, "|_no conservation");
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
                            Law * const       law =  Coerce(laws).pushTail( new Law() );
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
                    Coerce(rg) = MKL::Rank::Of(Qm);
                    Y_XMLog(xml, "Qm = " << Qm);
                    Y_XMLog(xml, "nu = " << topo.nu);
                    Y_XMLog(xml, "Nc = " << Nc);
                    Y_XMLog(xml, "rg = " << rg);

                }
            }
        }
    }

}
