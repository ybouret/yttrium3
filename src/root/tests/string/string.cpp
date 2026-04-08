#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/type/conversion.hpp"

using namespace Yttrium;

Y_UTEST(string)
{
    Y_SIZEOF(Core::String<char>);
    Y_SIZEOF(Core::String<uint32_t>);

    String s = "Hello"; std::cerr << s << std::endl;
    

}
Y_UDONE()

