#include "y/string.hpp"
#include "y/concurrent/threaded.hpp"
#include "y/memory/auto-built.hpp"
#include "y/utest/run.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"

using namespace Yttrium;


namespace
{
    static const size_t NumThreads = 8;

    class Testing
    {
    public:

        Testing() : mutex(), cond(), ready(0)
        {}

        ~Testing() noexcept
        {
        }

        void Run()
        {
            mutex.lock();
            (std::cerr << "Entering #" << ready+1 << std::endl).flush();
            if(++ready<NumThreads)
            {
                cond.wait(mutex);
            }
            else
            {
                cond.broadcast();
                (std::cerr << "syncronized!" << std::endl).flush();
            }
            mutex.unlock();

        }

        Concurrent::Mutex     mutex;
        Concurrent::Condition cond;
        size_t                 ready;

    private:
        Y_Disable_Copy_And_Assign(Testing);

    };
}

Y_UTEST(string_in_threads)
{
    static const size_t Requested = sizeof(Concurrent::Threaded) * NumThreads;
    static void * wksp[ Alignment::WordsGEQ<Requested>::Count ];

    Testing testing;

    Memory::AutoBuilt<Concurrent::Threaded> threads(testing, & Testing::Run, Y_BZero(wksp), NumThreads);

}
Y_UDONE()

