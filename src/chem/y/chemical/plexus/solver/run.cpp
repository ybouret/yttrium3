#include "y/chemical/plexus/solver.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        Solver::Outcome Solver:: run(XML::Log        & xml,
                                     XWritable       & C,
                                     const Level       L,
                                     const XReadable & K)
        {
            const size_t count = cls.elist->size;
            Y_XML_Element_Attr(xml,SolverRun, Y_XML_Attr(count) );

            //------------------------------------------------------------------
            //
            // build basis from running eqs
            //
            //------------------------------------------------------------------
            const size_t n = buildBasis(xml,C,L,K);

            //------------------------------------------------------------------
            //
            // Initialize starting point
            //
            //------------------------------------------------------------------
            Indexed::Transfer(Cini,SubLevel,C,L,cls.slist);
            const xreal_t F0 = F(C,L);
            Y_XMLog(xml, "F0 = " << F0.str());

            //------------------------------------------------------------------
            //
            // optimize local objective function over 1D ansatzs
            //
            //------------------------------------------------------------------
            if(Trace)
            {
                trace.free();
                tropt.free();
            }


            const Ansatz * bestLocal = 0;
            for(size_t i=1;i<=n;++i)
            {
                Ansatz & a  = ans[i];
                if(optimizing(xml,a,F0,i))
                {
                    if(!bestLocal || a.F1 < bestLocal->F1)
                    {
                        bestLocal = &a;
                    }
                }
            }

            if(bestLocal)
            {
                Y_XMLog(xml, "[+bestLocal] F = " << bestLocal->F1.str() << " @" << bestLocal->eq.name);
            }
            else
            {
                Y_XMLog(xml, "[-bestLocal]");
            }


            //------------------------------------------------------------------
            //
            // optimize glocal objective function with jacobian of local basis
            //
            //------------------------------------------------------------------
            const bool bestGlobal = NRStep(xml,F0,C,L);
            if(bestGlobal)
            {
                Y_XMLog(xml, "[+bestGlobal] F = " << Fg.str() );
            }
            else
            {
                Y_XMLog(xml, "[-bestGlobal]");
            }


            if(Trace)
            {
                std::cerr << trace << std::endl;
                std::cerr << tropt << std::endl;
            }


            if(bestLocal)
            {
                //--------------------------------------------------------------
                //
                // GOT local improvement
                //
                //--------------------------------------------------------------
                if(bestLocal)
                {
                    //----------------------------------------------------------
                    // AND global improvement : keep best of both
                    //----------------------------------------------------------

                    if(Fg<bestLocal->F1)
                    {
                        Y_XMLog(xml,"[global/local]");
                        Indexed::Transfer(C,L,Cend,SubLevel,cls.slist);
                    }
                    else
                    {
                        Y_XMLog(xml,"[local/global]");
                        Indexed::Transfer(C,L,bestLocal->cc,SubLevel,cls.slist);
                        Fg = bestLocal->F1;
                    }


                    return Fg.mantissa <= 0 ? Achieved : Improved;
                }
                else
                {
                    //----------------------------------------------------------
                    // BUT no global improvement: keep local
                    //----------------------------------------------------------
                    Y_XMLog(xml,"[local] ");
                    Indexed::Transfer(C,L,bestLocal->cc,SubLevel,cls.slist);
                    Fg = bestLocal->F1;
                    return Fg.mantissa <= 0 ? Achieved : Improved;
                }
            }
            else
            {
                //--------------------------------------------------------------
                //
                // NO local improvement
                //
                //--------------------------------------------------------------
                if(bestGlobal)
                {
                    //----------------------------------------------------------
                    // BUT global improvement
                    //----------------------------------------------------------
                    Y_XMLog(xml,"[global]");
                    Indexed::Transfer(C,L,Cend,SubLevel,cls.slist);
                    return Fg.mantissa <= 0 ? Achieved : Improved;
                }
                else
                {
                    //----------------------------------------------------------
                    // NO  global improvement EITHER
                    //----------------------------------------------------------
                    Y_XMLog(xml,"[stalled]");
                    Fg = F0;
                    return Fg.mantissa <= 0 ? Achieved : Spurious;
                }
            }

        }

    }

}


