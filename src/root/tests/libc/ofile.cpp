
#include "y/libc/file/output.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(libc_ofile)
{
    if(argc>1)
    {
        Libc::OutputFile F(argv[1]);
        F.write('H');
        F.write("ello",4);
    }
}
Y_UDONE()
