#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Reactor::Outcome Reactor:: run(XML::Log &xml, XWritable &C, const Level L, const XReadable &K)
        {
            Y_XML_Element(xml,ReactorRun);

            //------------------------------------------------------------------
            //
            //
            // initialize for consistency
            //
            //
            //------------------------------------------------------------------
            F0.ldz();
            basis.free();

            //------------------------------------------------------------------
            //
            //
            // build RUNNING assays, tweaking C
            //
            //
            //------------------------------------------------------------------
            const size_t na = buildAssays(xml,C,L,K);
            Y_XMLog(xml,"#assay = " << na);
            if(na<=0)
            {
                return Achieved;
            }

            //------------------------------------------------------------------
            //
            //
            // initialize from assays
            //
            //
            //------------------------------------------------------------------
            Indexed::Transfer(Cini,SubLevel,C,L,cluster.slist);
            F0 = Fs = ObjectiveFunction(Cini,SubLevel);
            Y_XMLog(xml,"F0 = " << F0.str());

            //------------------------------------------------------------------
            //
            //
            // study and optimize assays
            //
            //
            //------------------------------------------------------------------
            const size_t        ok     = studyAssays(xml);
            const Assay * const best1D = (ok<=0) ? 0 : & assays[1];
            if(best1D)
            {
                Y_XMLog(xml, "[best1D] " << best1D->F1.str() << " @" << best1D->eq.name);
            }
            else
            {
                Y_XMLog(xml, "[best1D] NONE");
            }

            //------------------------------------------------------------------
            //
            //
            // create local basis
            //
            //
            //------------------------------------------------------------------
            createBasis(xml);

            //------------------------------------------------------------------
            //
            //
            // Newton Raphson step
            //
            //
            //------------------------------------------------------------------
            const bool hasNRS = builtNRStep(xml);
            if(hasNRS)
            {
                Y_XMLog(xml, "[hasNRS] " << Fs.str() );
            }
            else
            {
                Y_XMLog(xml, "[hasNRS] NONE");
            }

            if(Trace)
            {
                std::cerr << gpStd << std::endl;
                std::cerr << gpOpt << std::endl;
            }


            return Spurious;
        }

    }

}

