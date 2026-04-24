
#include "y/ascii/convert.hpp"
#include "y/libc/str/len.h"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(ascii_conv_u64)
{
    for(int i=1;i<argc;++i)
    {
        const char * const text = argv[i];
        const size_t       size = Yttrium_Strlen(text);
        std::cerr << "'" << text << "' => ";
        const uint64_t     u64 = ASCII::Convert::ToU64(text,size,"argv",0);
        std::cerr << u64 << std::endl;
    }
}
Y_UDONE()
