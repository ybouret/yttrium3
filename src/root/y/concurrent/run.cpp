
#include "y/concurrent/run.hpp"


namespace Yttrium
{
    namespace Concurrent
    {

        RunData:: ~RunData() noexcept
        {
        }

        RunData * Run:: self() noexcept { return this; }

        Run:: ~Run() noexcept
        {
        }
        
    }

}


