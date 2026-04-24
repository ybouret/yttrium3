#include "y/system/hardware.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_hw)
{
    Y_PRINTV( Hardware::NumProcs() );
}
Y_UDONE()
