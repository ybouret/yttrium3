#include "y/concurrent/api/engine.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Y_Proxy_Impl(Engine,*simd)

        Engine:: ~Engine() noexcept
        {
            assert(simd);
            if(simd->liberate())
            {
                delete simd;
            }
            Coerce(simd) = 0;
        }

        Engine:: Engine(const Sequential_ &) :
        Proxy<SIMD>(),
        simd( SIMD::NewSequential() )
        {
            simd->withhold();
        }

        Engine:: Engine(const Engine &engine) noexcept :
        Proxy<SIMD>(),
        simd( engine.simd )
        {
            simd->withhold();
        }

    }
}
