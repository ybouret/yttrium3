#include "y/jive/source.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(jive_source)
{
    Core::Rand ran;

    Y_SIZEOF(Identifier);
    Y_SIZEOF(Jive::Spot);
    Y_SIZEOF(Jive::Char);
    Y_SIZEOF(Jive::Token);
    Y_SIZEOF(Jive::Module);

    if(argc>1)
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        char         buffer[8];
        while(true)
        {
            source.fetch(ran.in<size_t>(1,10));
            if( ran.tails() )
            {
                char c = 0;
                if(!source.query(c)) break;
                std::cerr << c;
            }
            else
            {
                const size_t numRead = source.query(buffer,sizeof(buffer));
                if(numRead<=0) break;
                for(size_t i=0;i<numRead;++i)
                    std::cerr << buffer[i];
            }
        }


    }

}
Y_UDONE()

