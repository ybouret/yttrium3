#include "y/system/error.hpp"
#include "y/utest/run.hpp"

#include <cerrno>

using namespace Yttrium;

Y_UTEST(system_error)
{
    char buffer[1024];

    Libc::Error::Format(buffer,sizeof(buffer),EINVAL);
    std::cerr << buffer << std::endl;

    Windows::Error::Format(buffer,sizeof(buffer),1);
    std::cerr << buffer << std::endl;

#if defined(Y_Darwin)
    Mach::Error::Format(buffer, sizeof(buffer),1);
    std::cerr << buffer << std::endl;
#endif

    //Libc::Error::Critical(EINVAL, "in %s at line:%d", test, __LINE__);

}
Y_UDONE()

