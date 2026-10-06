
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/string/tokenizer.hpp"
#include "y/string.hpp"
#include "y/stream/proc/input.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/format/percent.hpp"

using namespace Yttrium;

namespace
{
    static inline
    size_t Load(Vector<String> &installed)
    {
        static const char cmd[] = "port installed";

        InputProcess  fp(cmd);
        String        line;
        Vector<String> words;
        size_t         count = 0;
        while(fp.gets(line))
        {
            if(++count<=1) continue;
            words.free();
            Tokenizer::AppendTo(words,line," \t");
            if(words.size()<=0) continue;
            installed << words[1];
        }
        return installed.size();
    }

    static inline
    bool Needs(const String &needed,
               const String &portName,
               const size_t  portIndx,
               const size_t  numPorts)
    {
        const String cmd = "port deps " + portName;
        const String progress = Percent::Get(portIndx,numPorts);

        (std::cerr << "[" << progress << "]  \r").flush();
        InputProcess fp(cmd);
        String line;
        size_t count = 0;
        Vector<String> parts;
        Vector<String> words;
        while( fp.gets(line) )
        {
            if(++count<=1) continue;
            parts.free();
            Tokenizer::AppendTo(parts,line,':');
            if(parts.size()!=2) continue;
            words.free();
            Tokenizer::AppendTo(words,parts[2],',');
            for(size_t i=words.size();i>0;--i)
            {
                String &deps = Algorithm::Crop(words[i],isblank);
                if(needed == deps)
                    return true;
            }
        }

        return false;
    }



}

Y_PROGRAM()
{
    if(argc<=1)
    {
        std::cerr << "usage: " << program << " portName" << std::endl;
        return 1;
    }

    const String   needed = argv[1];
    Vector<String> installed;
    const size_t n = Load(installed);
    for(size_t i=1;i<=n;++i)
    {
        const String & portName = installed[i];
        if( Needs(needed,portName,i,n) )
        {
            std::cout << portName << "            " << std::endl;
        }
    }
    std::cout << std::endl;
}
Y_EXECUTE()

