#include "y/concurrent/run.hpp"
#include "y/ability/lockable.hpp"
#include "y/utest/run.hpp"

#include <cassert>

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



    class Dummy
    {
    public:
        Dummy()
        {
        }

        ~Dummy() noexcept
        {
        }

        void something(void)
        {
            {
                Y_Giant_Lock();
                std::cerr << "dummy.something" << std::endl;
            }
        }

        void anything(Lockable &lock)
        {
            {
                Y_Lock(lock);
                std::cerr << "dummy.anything" << std::endl;
            }
        }

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };


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
    
    {
        Dummy           dum;
        Concurrent::Run run0( dum, & Dummy::something );
        Concurrent::Run run1( dum, & Dummy::anything, Lockable::Giant() );
    }
    std::cerr << "End Of Program" << std::endl;
}
Y_UDONE()

