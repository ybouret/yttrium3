#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_mutex)
{
    Concurrent::Mutex mutex;
    {
        Y_Lock(mutex);
        std::cerr << "Locked-1" << std::endl;
        {
            Y_Lock(mutex);
            std::cerr << "Locked-2" << std::endl;
        }
    }
}
Y_UDONE()

