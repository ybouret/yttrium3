
#include "y/chemical/plexus/reactor.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        bool Reactor:: transform(XML::Log        & xml,
                                 XWritable       & C,
                                 const Level       L,
                                 const XReadable & K,
                                 const size_t      maxCycle)
        {
            Y_XML_Element(xml,Transform);

            if(Trace)
            {
                const String fn = Formatted::Get("solver%s.dat", Decimal(cluster.gvid).c_str());
                OutputFile::Overwrite(fn);
            }

            const bool debug = (maxCycle > 0);
            size_t     cycle = 0;
        CYCLE:
            Y_XMLog(xml,"cycle #" << cycle);
            const Outcome outcome = run(xml,C,L,K);
            if(Trace)
            {
                const String fn = Formatted::Get("solver%s.dat", Decimal(cluster.gvid).c_str());
                OutputFile   fp(fn,true);
                fp("%s %.15g\n",Decimal(cycle).c_str(), (double) Fs);
            }

            switch(outcome)
            {
                case Achieved: Y_XMLog(xml, "[Achieved]"); return true;
                case Improved: Y_XMLog(xml, "[Improved]"); break;
                case Spurious: Y_XMLog(xml, "[Spurious]"); return false;
            }

            ++cycle;
            if(debug && cycle>=maxCycle) return false;
            goto CYCLE;


        }
    }

}
