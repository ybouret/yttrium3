#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(exception)
{
    Exception excp;
    excp.display(std::cerr);
}
Y_UDONE()


