
#include "y/chemical/plexus/combinatorics.hpp"
#include "y/container/cxx/series.hpp"


#include "y/coven/compress.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/counting/combination.hpp"
#include "y/coven/survey/standard.hpp"
#include "y/coven/survey/inquiry.hpp"

#include "y/handy/joint/set.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Combinatorics:: ~Combinatorics() noexcept
        {
        }


        namespace
        {
            
        }



        Combinatorics:: Combinatorics(XML::Log   & xml,
                                      Topology   & topo,
                                      Equilibria & eqs)
        {
            Y_XML_Element(xml,BuildCombinatorics);
            static const size_t MinCof = 2;
            static const char   CallSign[] = "Combinatorics";

            Coven::StandardSurvey  primary(MinCof);
            const size_t           N  = topo.N;     // max equilibria
            const IMatrix &        nuT = topo.nuT;

            {
                Matrix<apz>    mu;
                Y_XMLog(xml,"nuT = " << nuT);
                if( !Coven::Compress::Build(mu,topo.nuT,Coven::Compress::Duplicate,MinCof) )
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

                size_t                replicae = 0;
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
                            //Y_XMLog(xml,"Q = " << Q);

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

            typedef Handy::JointSet<size_t> iSet;
            typedef iSet::CacheType         iCache;
            typedef iSet::NodeType          iNode;


            const size_t  M  = topo.M; // species
            CxxArray<int> sto(M);
            CxxArray<int> w(N);


            iCache cache;
            iSet   input(cache), output(cache);

            for(const Coven::Vector *v=primary->head;v;v=v->next)
            {
                Y_XMLog(xml,*v);
                const Readable<apz> &W = *v;
                input.free();
                output.free();

                sto.ld(0);
                for(size_t i=N;i>0;--i) {

                    // extract coefficient
                    const apz & Wi = W[i];
                    switch(Wi.s)
                    {
                        case __Zero__: continue;
                        case Negative:
                        case Positive:
                            if( !W[i].tryCast(w[i]) ) {
                                const String s = Wi.toDec();
                                throw Specific::Exception(CallSign,"overflow coefficient %s",s.c_str());
                            }
                    }
                    const Readable<int> & nu = topo.nu[i];
                    const int             wi = w[i]; assert(wi);
                    for(size_t j=M;j>0;--j)
                    {
                        const int nu_j = nu[j]; if(!nu_j) continue;
                        input |= j;
                        sto[j] += nu_j * wi; // TODO check product
                    }
                }
                std::cerr << "sto=" << sto << std::endl;
                for(size_t j=M;j>0;--j)
                {
                    const int cf = sto[j]; if(!cf) continue;
                    output |= j;
                }
                std::cerr << input << " => " << output << std::endl;
                if(! input.contains(output) ) throw Specific:: Exception(CallSign,"corrupted weights!!");
                input -= output;
                std::cerr << "missing=" << input << std::endl;
            }



        }


    }

}
