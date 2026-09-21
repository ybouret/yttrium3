#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: NRStep(XML::Log        & xml,
                             const xreal_t     F0,
                             const XReadable & C,
                             const Level       L)
        {
            Y_XML_Element(xml,NewtonRaphson);
            Y_XMLog(xml, "F0=" << F0.str());

            /**/ if(!computeStep(xml,C,L)) return false;
            /**/     approveStep(xml);


            const xreal_t F1 = F(Cend,SubLevel);
            Y_XMLog(xml, "F1=" << F1.str());

            if(Trace)
            {
                OutputFile fp("nr-step.ycp");
                saveProfile(fp,TracePoints);
            }

            // TODO: study / optimize


            return false;
        }
    }
}
