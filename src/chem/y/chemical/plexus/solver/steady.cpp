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
                const bool   res = run(xml,C,L,K);
                const String out = Fg.str();
                Y_XMLog(xml, "[cycle #" << cycle << " | F = " << out << "]");
                if(Trace)
                {
                    OutputFile fp(runfn,true);
                    fp("%u %s\n", cycle, out.c_str() );
                }
                if( !res || (debug && cycle>=maxCycles) )
                    break;
            }

        }
    }

}

