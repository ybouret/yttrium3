
#include "y/concurrent/api/simd.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        
        SIMD:: SIMD() noexcept : procedure(0), arguments(0) {}

        SIMD:: ~SIMD() noexcept
        {
        }


        void SIMD:: Call0(Context &ctx, Arguments &args)
        {
            VaArgs ap(args);
            ap.func<Proc0>()(ctx);
        }

        void SIMD:: operator()(Proc0 func)
        {
            assert(!procedure);
            assert(!arguments);
            assert(0!=func);

            Arguments                    args(func);
            const Temporary<Arguments *> tmpArgs(arguments,&args);
            const Temporary<Procedure>   tmpProc(procedure,Call0);
            run();
        }

    }

}


