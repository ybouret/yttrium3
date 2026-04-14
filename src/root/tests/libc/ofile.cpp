
#include "y/libc/file/output.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(libc_ofile)
{
    if(argc>1)
    {
        Libc::OutputFile F(argv[1]);

    }
}
Y_UDONE()
