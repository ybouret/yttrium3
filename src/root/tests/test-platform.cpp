#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(platform)
{
    std::cerr << "test: " << test << std::endl;
    throw Exception();
}
Y_UDONE()
