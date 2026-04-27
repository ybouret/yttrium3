
#include "y/concurrent/api/simd.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        SIMD:: Arguments:: Arguments(const CopyOf_ &, void * const user) noexcept :
        addr(user),
        arg1(0)
        {
        }



        SIMD:: Arguments:: ~Arguments() noexcept {}

        SIMD:: SIMD() noexcept : procedure(0), arguments(0) {}

        SIMD:: ~SIMD() noexcept
        {
        }


        void SIMD:: CallFunc0(Context &ctx, Arguments &args)
        {
            assert(args.addr);
            union {
                void * addr;
                void (*func)(Context &);
            } alias = { args.addr };
            assert(alias.func);
            alias.func(ctx);
        }

        void SIMD:: operator()( void (*func)(Context &) )
        {
            assert(!procedure);
            assert(!arguments);
            assert(func);
            Arguments                    args(CopyOf,(void*)func);
            const Temporary<Arguments *> tmpArgs(arguments,&args);
            const Temporary<Procedure>   tmpProc(procedure,CallFunc0);
            run();
        }

    }

}


