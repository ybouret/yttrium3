#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/threaded.hpp"
#include "y/memory/auto-built.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/core/list/cxx.hpp"
#include "y/core/rand.hpp"
#include "y/system/wall-time.hpp"
#include "y/check/crc32.hpp"


using namespace Yttrium;

namespace  {

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
            long seed = 0;
            mutex.lock();
            (std::cerr << "Apex: Entering #" << ready+1 << std::endl).flush();
            if(++ready<NumThreads)
            {
                cond.wait(mutex);
            }
            else
            {
                cond.broadcast();
                (std::cerr << "Apex: synchronized!" << std::endl).flush();
            }
            {
                const uint64_t t = System::WallTime::Ticks();
                seed  = (long) CRC32::Run(t);
            }
            mutex.unlock();
            Core::Rand ran(seed);

            for(size_t iter=0;iter<256;++iter)
            {
                const apq lhs(ran, ran.in<size_t>(0,20), ran.in<size_t>(1,20) );
                const apq rhs(ran, ran.in<size_t>(1,20), ran.in<size_t>(1,20) );
                const apq sum  = lhs + rhs;
                const apq dif  = lhs - rhs;
                const apq prod = lhs * rhs;
                const apq rho  = lhs/rhs;
                if( ran() > 0.9f )
                {
                    Y_Lock(mutex);
                    (std::cerr << prod << std::endl).flush();
                }
            }



        }

        Concurrent::Mutex      mutex;
        Concurrent::Condition  cond;
        size_t                 ready;

    private:
        Y_Disable_Copy_And_Assign(Testing);

    };

}


Y_UTEST(apex_in_threads)
{
    static const size_t Requested = sizeof(Concurrent::Threaded) * NumThreads;
    static void * wksp[ Alignment::WordsGEQ<Requested>::Count ];


    Testing testing;
    Memory::AutoBuilt<Concurrent::Threaded> threads(testing, & Testing::Run, Y_BZero(wksp), NumThreads);
}
Y_UDONE()

