#include "y/concurrent/threaded.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Worker
    {
    public:
        inline Worker()
        {
        }

        inline ~Worker() noexcept
        {
        }

        Concurrent::Mutex mutex;

        inline void work()
        {
            { Y_Lock(mutex); (std::cerr << "In work()" << std::endl).flush(); }
        }

        inline void workInt(const int a)
        {
            { Y_Lock(mutex); (std::cerr << "In work(" << a << ")" << std::endl).flush(); }
        }



    private:
        Y_Disable_Copy_And_Assign(Worker);
    };
}
Y_UTEST(concurrent_threaded)
{

    Worker worker;

    const int value = 7;
    Concurrent::Threaded t1(worker, & Worker:: work);
    Concurrent::Threaded t2(worker, & Worker:: work);
    Concurrent::Threaded t3(worker, & Worker:: workInt, value);



}
Y_UDONE()

