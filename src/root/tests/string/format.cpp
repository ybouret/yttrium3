
#include "y/string/format.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(string_format)
{
    String str = Formatted::Get("%s:%d: formattted!",__FILE__,__LINE__);
    std::cerr << str << std::endl;
}
Y_UDONE()
