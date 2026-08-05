
#include "y/concurrent/api/simd.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

#if 0
        SIMD:: Arguments:: Arguments(const CopyOf_ &, void * const user) noexcept :
        addr(user),
        arg1(0),
        arg2(0),
        meth(0)
        {
        }



        SIMD:: Arguments:: ~Arguments() noexcept {}
#endif

        SIMD:: SIMD() noexcept : procedure(0), arguments(0) {}

        SIMD:: ~SIMD() noexcept
        {
        }


        void SIMD:: CallFunc0(Context &ctx, Arguments &args)
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
            const Temporary<Procedure>   tmpProc(procedure,CallFunc0);
            run();
        }

    }

}


