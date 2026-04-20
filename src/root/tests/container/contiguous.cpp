#include "y/container/contiguous/ro.hpp"
#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(container_contiguous)
{

    ReadOnlyContiguous<String> ros;
    (String&)ros = "Hello";

    std::cerr << ros << std::endl;

    Iter::Test::ForwardConst(ros);
    Iter::Test::ReverseConst(ros);

}
Y_UDONE()


