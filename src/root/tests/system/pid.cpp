#include "y/system/pid.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_pid)
{
    std::cerr << "pid=" << System::ProcessID::Get() << std::endl;
}
Y_UDONE()
