#include "y/system/exception.hpp"
#include "y/utest/run.hpp"
#include <cerrno>

using namespace Yttrium;

static inline void displayExcp(const Exception &excp)
{
    excp.display(std::cerr);
}

Y_UTEST(system_exception)
{
    {
        Libc::Exception excp(ENOMEM,"Demo at line %d", __LINE__);
        displayExcp(excp);
    }

    {
        Windows::Exception excp(1,"Demo at line %d", __LINE__);
        displayExcp(excp);
    }

#if defined(Y_Darwin)
    {
        Mach::Exception excp(1,"Demo at line %d", __LINE__);
        displayExcp(excp);
    }
#endif // defined(Y_Darwin)

}
Y_UDONE()


