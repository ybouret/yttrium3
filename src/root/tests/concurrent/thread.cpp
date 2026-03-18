#include "y/concurrent/thread.hpp"
#include "y/ability/lockable.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    struct Parameters
    {
        Lockable * sync;
    };

    static inline
    void DoSomething(void * const args)
    {
        Y_ASSERT(args);
        Parameters & params = *static_cast<Parameters *>(args);
        {
            Y_Lock(*params.sync);
            (std::cerr << "In Thread!" << std::endl).flush();
        }
    }



}

Y_UTEST(concurrent_thread)
{
    Parameters params = { & Lockable::Giant() };
    {
        Concurrent::Thread thread(DoSomething,&params);
        {
            Y_Lock(*params.sync);
            std::cerr << "In Thread Scope" << std::endl;
        }

    }
    std::cerr << "End Of Program" << std::endl;
}
Y_UDONE()

