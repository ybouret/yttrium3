
#include "y/chemical/plexus/combinatorics.hpp"
#include "y/chemical/plexus/combinatorics/stoichio.hpp"
#include "y/chemical/plexus/combinatorics/mixed.hpp"

#include "y/coven/survey/standard.hpp"
#include "y/handy/joint/set.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Combinatorics:: ~Combinatorics() noexcept
        {
        }

        const char * const Combinatorics::CallSign = "Combinatorics";


       
        namespace
        {
            typedef Handy::JointSet<size_t>    iSet;
            typedef iSet::CacheType            iCache;
        }



        Combinatorics:: Combinatorics(XML::Log        & xml,
                                      Topology        & topo,
                                      Equilibria      & eqs,
                                      const XReadable & K)
        {
            Y_XML_Element(xml,BuildCombinatorics);


            //--------------------------------------------------------------
            //
            //
            // Build all primary weights
            //
            //
            //--------------------------------------------------------------
            Coven::StandardSurvey  primary(MinCoeff);
            buildPrimary(primary,xml,topo);


            //--------------------------------------------------------------
            //
            //
            // Convert primary into mixed equilibria
            //
            //
            //--------------------------------------------------------------
            const size_t N  = topo.N;  // eqs
            const size_t M  = topo.M; // species
            StoichioDB   stoDB;
            iCache       cache;
            iSet         input(cache);
            iSet         output(cache);
            iArray       sto(M);
            iArray       w(N);
            size_t       maxOrder = 0;
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
                w.ld(0);

                //--------------------------------------------------------------
                //
                //
                // build sto = nu * weight
                //
                //
                //--------------------------------------------------------------
                const Readable<apz> &W     = *v;
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
                                    throw Specific::Exception(CallSign,"overflow coefficient=%s",s.c_str());
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
                //Y_XMLog(xml, (use ? "[+]" : "[-]") << " " << w << " : \\" << input << " : " << sto);
                if(!use) continue;

                //--------------------------------------------------------------
                //
                //
                // Collecting equilibria
                //
                //
                //--------------------------------------------------------------
                EList emx;
                IList ecf;
                for(ENode *en=topo.group->head;en;en=en->next)
                {
                    Equilibrium &eq = **en;
                    const size_t ei = eq.indx[SubLevel];
                    const int    cf = w[ei];
                    if(!cf) continue;
                    emx << eq;
                    ecf << cf;
                }
                //std::cerr << "|_emx=" << emx << std::endl;
                //std::cerr << "|_ecf=" << ecf << std::endl;

                //--------------------------------------------------------------
                //
                //
                // Collecting species
                //
                //
                //--------------------------------------------------------------
                SList smx;
                IList scf;
                for(SNode *sn=topo.slist->head;sn;sn=sn->next)
                {
                    const Species &sp = **sn;
                    const size_t   sj = sp.indx[SubLevel];
                    const int      cf = sto[sj];
                    if(!cf) continue;
                    smx << sp;
                    scf << cf;
                }
                //std::cerr << "|_smx=" << smx << std::endl;
                //std::cerr << "|_scf=" << scf << std::endl;

                EqPtr eq( MixedEquilibrium::Create(eqs->size()+1,emx,ecf, smx, scf, K) );
                eqs.add(eq);
                if(xml.verbose)
                    eqs.EqFormat::print(xml() << "[+] ",*eq,false,0.0);
                Coerce(topo.elist) << *eq;
            }

            Indexed::SubLabel( Indexed::TopHSort( Coerce(topo.elist) ) );


            Y_XML_Element(xml,Summary);
            Y_XMLog(xml,"initial equilibria: " << topo.group->size);
            Y_XMLog(xml,"created equilibria: " << stoDB->size);
            Y_XMLog(xml,"all     equilibria: " << topo.elist->size);



        }


    }

}
