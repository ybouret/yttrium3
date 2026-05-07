#include "y/stream/gz/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_gz_in)
{
    if(argc>1)
    {
        {
            GZ::Input fp(argv[1]);
            char c = 0;
            while(fp.query(c))
                std::cerr << c;
            std::cerr << "[EOF]" << std::endl;
        }

        {
            GZ::Input fp(argv[1]);
            String    line;
            while( fp.gets(line) )
                std::cerr << line << std::endl;
            std::cerr << "[EOF]" << std::endl;
        }

        {
            GZ::Input fp(argv[1]);
            char      block[16];
            while(true)
            {
                const size_t nr = fp.query(block,sizeof(block));
                for(size_t i=0;i<nr;++i) std::cerr << block[i];
                if(nr<sizeof(block)) break;
            }
            std::cerr << "[EOF]" << std::endl;
        }



    }
}
Y_UDONE()
