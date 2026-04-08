#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/type/conversion.hpp"

using namespace Yttrium;

Y_UTEST(string)
{
    Y_SIZEOF(Core::String<char>);
    Y_SIZEOF(Core::String<uint32_t>);

    Y_CHECK(Y_Is_SuperSubClass_Strict(LegacyString,String));

    //String s;

}
Y_UDONE()

