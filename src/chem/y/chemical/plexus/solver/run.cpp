#include "y/chemical/plexus/solver.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: run(XML::Log        & xml,
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
            // optimize local objective function over 1D
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
                Y_XMLog(xml, "[+bestLocal] " << bestLocal->F1.str() << " @" << bestLocal->eq.name);
            }
            else
            {
                Y_XMLog(xml, "[-bestLocal]");
            }


            const bool bestGlobal = NRStep(xml,F0,C,L);
            if(bestGlobal)
            {
                Y_XMLog(xml, "[+bestGlobal] " << Fg.str() );
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

        }

    }

}


