

#include "y/ascii/convert.hpp"
#include "y/libc/str/len.h"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(ascii_conv_i64)
{
    for(int i=1;i<argc;++i)
    {
        const char * const text = argv[i];
        const size_t       size = Yttrium_Strlen(text);
        std::cerr << "'" << text << "' => ";
        const int64_t     i64 = ASCII::Convert::ToI64(text,size);
        std::cerr << i64 << std::endl;
    }
}
Y_UDONE()
