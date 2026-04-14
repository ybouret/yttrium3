#include "y/libc/file/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(libc_ifile)
{
    if(argc>1)
    {
        Libc::InputFile F(argv[1]);
        char C = 0;
        while(F.query(C))
            std::cerr << C;
    }
}
Y_UDONE()
