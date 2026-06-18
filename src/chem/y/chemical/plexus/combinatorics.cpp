
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
            static const char   CallSign[] = "Combinatorics";
            static const size_t MinCoeff = 2;

        }

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


        namespace
        {
            typedef CxxArray<int> iArray;

            class Stoichio : public Object, public iArray
            {
            public:
                typedef CxxListOf<Stoichio> List;

                explicit Stoichio(const iArray &arr) :
                Object(),
                iArray(CopyOf,arr),
                next(0),
                prev(0)
                {
                }

                Stoichio *next;
                Stoichio *prev;

            private:
                Y_Disable_Copy_And_Assign(Stoichio);
            };

            class StoDB : public Proxy<const Stoichio::List>
            {
            public:
                inline explicit StoDB() noexcept  : list() {}
                inline virtual ~StoDB() noexcept {}

                bool mayUse(const iArray &rhs)
                {
                    for(const Stoichio *node=list.head;node;node=node->next)
                    {
                        const Stoichio &lhs = *node;
                        if( lhs == rhs )
                            return false;
                    }

                    list.pushTail(new Stoichio(rhs));
                    return true;
                }


            private:
                Y_Disable_Copy_And_Assign(StoDB);
                Y_Proxy_Decl() { return list; }

                CxxListOf<Stoichio> list;

            };

        }

        Combinatorics:: Combinatorics(XML::Log   & xml,
                                      Topology   & topo,
                                      Equilibria & eqs)
        {
            Y_XML_Element(xml,BuildCombinatorics);
            Coven::StandardSurvey  primary(MinCoeff);
            buildPrimary(primary,xml,topo);



            typedef Handy::JointSet<size_t> iSet;
            typedef iSet::CacheType         iCache;

            const size_t  N  = topo.N;  // eqs
            const size_t  M  = topo.M; // species


            StoDB  stoDB;
            iCache cache;
            iSet   input(cache);
            iSet   output(cache);
            iArray sto(M);
            iArray w(N);
            size_t maxOrder = 0;
            for(const Coven::Vector *v=primary->head;v;v=v->next)
            {
                //--------------------------------------------------------------
                //
                //
                // prepare
                //
                //
                //--------------------------------------------------------------
                input.free();
                output.free();
                sto.ld(0);

                //--------------------------------------------------------------
                //
                //
                // build sto = nu * weight
                //
                //
                //--------------------------------------------------------------
                const Readable<apz> &W = *v;
                const size_t         order = v->ncof;
                InSituMax(maxOrder,order);
                {
                    for(size_t i=N;i>0;--i) {

                        //------------------------------------------------------
                        //
                        // extract coefficient
                        //
                        //------------------------------------------------------
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

                        //------------------------------------------------------
                        //
                        // cumulate into sto
                        //
                        //------------------------------------------------------
                        const Readable<int> & nu = topo.nu[i];
                        const int             wi = w[i]; assert(wi);
                        for(size_t j=M;j>0;--j)
                        {
                            const int nu_j = nu[j]; if(!nu_j) continue;
                            input |= j;
                            sto[j] += nu_j * wi; // TODO check product
                        }
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // check result
                //
                //
                //--------------------------------------------------------------

                for(size_t j=M;j>0;--j)
                {
                    const int cf = sto[j]; if(!cf) continue;
                    output |= j;
                }
                if(! input.contains(output) )        throw Specific:: Exception(CallSign,"corrupted weights!!");
                if( (input -= output)->size() <= 0 ) throw Specific:: Exception(CallSign,"no missing species detected!!");
                const bool use = stoDB.mayUse(sto);
                Y_XMLog(xml, (use ? "[+]" : "[-]") << " " << w << " : \\" << input << " : " << sto);
                if(!use) continue;

            }

            Y_XML_Element(xml,Summary);
            Y_XMLog(xml,"initial equilibria: " << topo.group->size);
            Y_XMLog(xml,"created equilibria: " << stoDB->size);



        }


    }

}
