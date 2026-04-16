#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_input_file)
{
    Core::Rand ran;

    if(argc>1)
    {
        std::cerr << "-- byte wise --" << std::endl;
        {
            InputFile fp(argv[1]);
            char c;
            while(fp.query(c)) std::cerr << c;
            std::cerr << "-- done/byte" << std::endl;
        }

        std::cerr << "-- block wise --" << std::endl;
        {
            InputFile fp(argv[1]);
            char buffer[BUFSIZ];
            while(true)
            {
                const size_t numRead = fp.query(buffer,sizeof(buffer));
                if(!numRead) break;
                for(size_t i=0;i<numRead;++i) std::cerr << buffer[i];
            }

            std::cerr << "-- done/block" << std::endl;
        }

        std::cerr << "-- string wise --" << std::endl;
        {
            InputFile fp(argv[1]);
            String    s;
            unsigned  i=0;
            while( fp.gets(s) )
            {
                ++i;
                std::cerr << std::setw(3) << i << ": '" << s << "'" << std::endl;
            }
            std::cerr << "-- done/string" << std::endl;

        }


    }
}
Y_UDONE()
