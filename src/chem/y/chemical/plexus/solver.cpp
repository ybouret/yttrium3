#include "y/chemical/plexus/solver.hpp"
#include "y/core/hsort.hpp"

namespace Yttrium
{
    namespace Chemical
    {



        Solver:: Solver( const Cluster  &cluster) :
        cls(cluster),
        Ceq(cls.elist->size,cls.M),
        ans(cls.elist->size),
        xmul(),
        xadd()
        {

        }



        Solver:: ~Solver() noexcept
        {
        }


        void Solver:: run(XML::Log        & xml,
                          XWritable       & C,
                          const Level       L,
                          const XReadable & K)
        {
            const size_t count = cls.elist->size;
            Y_XML_Element_Attr(xml,SolverRun, Y_XML_Attr(count) );


            //------------------------------------------------------------------
            //
            //
            // Regularize concentrations
            //
            //
            //------------------------------------------------------------------
            {
                Y_XML_Element(xml,Regularize);
            REGULARIZE:
                bool emergency = false;
                if(xml.verbose) {
                    cls.sfmt.display(*xml,cls.slist,"\t\t[",C,L,"]", xreal_t::ToString);
                }
                ans.free();
                for(const ENode *en=cls.elist->head;en;en=en->next)
                {
                    XWritable         & cc =  Indexed::Transfer(Ceq[ans.size()+1],SubLevel,C,L,cls.slist);
                    const Equilibrium & eq = **en;
                    const xreal_t       eK = eq(K,TopLevel);
                    const Aftermath     am = Aftermath::Compute(xml,cc,SubLevel,C,L,eq,eK,xmul,xadd);
                    switch(am.st)
                    {
                        case Blocked:
                            continue;
                        case Running:
                            if(!emergency)    ans.append(eq,eK,am,cc);
                            continue;
                        case Crucial:
                            emergency = true; ans.append(eq,eK,am,cc);
                            continue;
                    }
                }

                if(emergency)
                {
                    Y_XML_Element(xml,ProcessEmergency);
                    for(size_t i=ans.size();i>0;--i)
                    {
                        Ansatz &a = ans[i];
                        if( a.am.st == Running)
                        {
                            ans.demote(i);
                            ans.popTail();
                        }
                        else
                        {
                            assert( Crucial == a.am.st );
                        }
                    }

                    const size_t n = ans.size(); assert(n>=1);
                    Core::HSort::Make( &ans[1], n, Ansatz::IncreasingAX );
                    for(size_t i=1;i<=n;++i)
                    {
                        const Ansatz &a = ans[i]; assert(a.am.st==Crucial);
                        Y_XMLog(xml, "@xi = " << std::setw(22) << a.am.xi.str() << ", nz=" << std::setw(3) << a.am.nz << " : " << a.eq);
                    }

                    const Ansatz &winner = ans.head();
                    Indexed::Transfer(C, L, winner.cc, SubLevel,cls.slist);
                    goto REGULARIZE;
                }
            }

            //------------------------------------------------------------------
            //
            //
            // Select
            //
            //
            //------------------------------------------------------------------
            const size_t n_ok = ans.size();
            {
                Y_XMLog(xml, "Selecting #" << ans.size());
                for(size_t i=n_ok;i>0;--i)
                {
                    Ansatz  &a     = ans[i]; assert(a.am.st==Running);
                    Coerce(a.A0)  = a.affinity(xadd,C,L);
                }
                Core::HSort::Make( &ans[1], n_ok, Ansatz::DecreasingAA );

                if(xml.verbose)
                {
                    for(size_t i=1;i<=n_ok;++i)
                    {
                        const Ansatz  &a  = ans[i]; assert(a.am.st==Running);
                        Y_XMLog(xml, " @ xi = " << std::setw(22) << a.am.xi.str()
                                <<   " | A0 = " << std::setw(22) << a.A0.str()
                                <<   " | " << a.eq);
                    }
                }


            }





        }


    }
}
