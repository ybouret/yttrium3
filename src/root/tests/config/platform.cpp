#include "y/utest/run.hpp"
#include "y/config/platform.h"

using namespace Yttrium;

Y_UTEST(config_platform)
{
    std::cerr << "test: " << test << std::endl;
#if defined(_MSC_VER)
	Y_PRINTV(_MSC_VER);
#endif

}
Y_UDONE()
