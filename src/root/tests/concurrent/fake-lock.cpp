#include "y/concurrent/fake-lock.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_fake_lock)
{
    Concurrent::FakeLock fl;
    Concurrent::FakeLock::Verbose = true;

    std::cerr << "Using" << fl << std::endl;
    {
        Y_Lock(fl);
        {
            Y_Lock(fl);
        }
    }

    std::cerr << "End..." << std::endl;
}
Y_UDONE()


