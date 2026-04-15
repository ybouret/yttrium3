#include "y/libc/file/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(libc_ifile)
{
    if(argc>1)
    {
        {
            Libc::InputFile F(argv[1]);
            char C = 0;
            while(F.query(C))
                std::cerr << C;
        }

        {
            Libc::InputFile F(argv[1]);
            char         buffer[256];
            const size_t buflen = Y_Static_Size(buffer);
            while(true)
            {
                const size_t numRead = F.query(buffer,buflen);
                if(numRead<=0) break;
                for(size_t i=0;i<numRead;++i) std::cerr << buffer[i];
            }
        }
    }
}
Y_UDONE()
