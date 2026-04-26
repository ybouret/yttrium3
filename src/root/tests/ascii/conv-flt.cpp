



#include "y/ascii/convert.hpp"
#include "y/libc/str/len.h"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(ascii_conv_flt)
{
    for(int i=1;i<argc;++i)
    {
        const char * const text = argv[i];
        const size_t       size = Yttrium_Strlen(text);
        std::cerr << "'" << text << "' => ";
        const long double res = ASCII::Convert::ToFP<long double>(text,size);
        std::cerr << res << std::endl;
    }
}
Y_UDONE()
