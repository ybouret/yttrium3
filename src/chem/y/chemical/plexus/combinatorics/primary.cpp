
#include "y/chemical/plexus/combinatorics.hpp"
#include "y/chemical/plexus/combinatorics/stoichio.hpp"



#include "y/coven/compress.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/counting/combination.hpp"
#include "y/coven/survey/standard.hpp"
#include "y/coven/survey/inquiry.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        void Combinatorics :: buildPrimary(Coven::StandardSurvey &primary,
                                           XML::Log              &xml,
                                           Topology              &topo) const
        {
            Y_XML_Element(xml,BuildPrimary);

            Matrix<apz>            mu;
            const size_t           N  = topo.N;     // max equilibria
            const IMatrix &        nuT = topo.nuT;
            Y_XMLog(xml,"nuT = " << nuT);
            if( !Coven::Compress::Build(mu,topo.nuT,Coven::Compress::Duplicate,MinCoeff) )
            {
                Y_XMLog(xml,"No multiple used species");
                return;
            }
            const size_t R    = mu.rows;    // Repeated
            const size_t kmax = Min(R,N-1); // max simultaneous to probe
            Y_XMLog(xml, "mu  = " << mu);
            Y_XMLog(xml, "mutiple species : " << R);
            Y_XMLog(xml, "Hyperplane      : " << N-1);
            Y_XMLog(xml, "probing up to   : " << kmax);

            size_t replicae = 0;
            {
                Matrix<apz> Q;
                for(size_t k=1;k<=kmax;++k)
                {
                    Y_XML_Element_Attr(xml,Probing,Y_XML_Attr(k));
                    Matrix<apz> P(k,N);
                    Combination comb(R,k);
                    do
                    {
                        for(size_t i=k;i>0;--i)
                            P[i].load( mu[ comb[i] ] );
                        Y_XMLog(xml,"P = " << P );
                        if( !MKL::OrthoSpace::Eval(Q,P))
                        {
                            Y_XMLog(xml, "|_no orthogonal space!");
                            continue;
                        }

                        Coven::Inquiry<Coven::StandardSurvey> replica(Q,2,Coven::Tribes::Optimizing);
                        replicae += (*replica)->size;
                        replica.sendTo(primary);

                    } while( comb.next() );
                }
            }

            Y_XMLog(xml, "Sampling : " << std::setw(6) << primary.sampling);
            Y_XMLog(xml, "Replicae : " << std::setw(6) << replicae);
            Y_XMLog(xml, "To Build : " << std::setw(6) << primary->size);
        }


    }

}


