
#include "y/libc/file/copy.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

Y_UTEST(libc_file_copy)
{
    if(argc>2)
    {
        const String srcName = argv[1];
        const String tgtName = argv[2];
        Libc::InputFile  source(srcName);
        Libc::OutputFile target(tgtName);
        Libc::FileCopy::To(target,source);
    }
}
Y_UDONE()
