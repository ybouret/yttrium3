//! \file

#ifndef Y_Concurrent_Parallel_Run_Included
#define Y_Concurrent_Parallel_Run_Included 1

#include "y/concurrent/thread.hpp"

namespace Yttrium
{



    class ParallelRun : public Thread
    {
    public:


        virtual ~ParallelRun() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(ParallelRun);
    };
}


#endif // !Y_Concurrent_Parallel_Run_Included

