#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        void Solver:: steady(XML::Log        & xml,
                             XWritable       & C,
                             const Level       L,
                             const XReadable & K,
                             const size_t      maxCycles)
        {

            Y_XML_Element(xml,SolverSteady);
            if(Trace) OutputFile::Overwrite(runfn);
            const bool debug = maxCycles > 0;
            unsigned   cycle = 0;
            while(true)
            {
                ++cycle;
                const Outcome outcome = run(xml,C,L,K);
                const String  results = Fg.str();
                Y_XMLog(xml, "[cycle #" << cycle << " | F = " << results << "]");
                if(Trace)
                {
                    OutputFile fp(runfn,true);
                    fp("%u %s\n", cycle, results.c_str() );
                }

                if(debug && cycle>=maxCycles) break;

                switch(outcome)
                {
                    case Achieved: Y_XMLog(xml, "[Achieved]"); return;
                    case Improved: Y_XMLog(xml, "[Improved]"); continue;
                    case Spurious: Y_XMLog(xml, "[Achieved]"); return;
                }

            }

        }
    }

}

