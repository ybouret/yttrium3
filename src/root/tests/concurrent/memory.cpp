
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/auto-built.hpp"
#include "y/calculus/alignment.hpp"

using namespace Yttrium;



namespace
{
    static inline
    void MemoryInThread(void * const)
    {
        Lockable &sync = Lockable::Giant();
        {
            Y_Lock(sync);
            (std::cerr << "In Thread!" << std::endl).flush();
        }
    }

    class MyThread : public Concurrent::Thread
    {
    public:
        explicit MyThread() :
        Concurrent::Thread(MemoryInThread,0)
        {
        }

        virtual ~MyThread() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(MyThread);
    };
}

Y_UTEST(concurrent_memory)
{
    const size_t numThreads = 2;
    void *       wksp[ Alignment::WordsGEQ<numThreads*sizeof(MyThread)>::Count ];
    Memory::AutoBuilt<MyThread> threads(wksp,numThreads);
}
Y_UDONE()

