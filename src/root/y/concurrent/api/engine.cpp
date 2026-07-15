#include "y/concurrent/api/engine.hpp"
#include "y/concurrent/thread/venue.hpp"

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



        Engine:: Engine(const Engine &engine) noexcept :
        Proxy<SIMD>(),
        simd( engine.simd )
        {
            simd->withhold();
        }

        Engine:: Engine(SIMD * const user) noexcept :
        Proxy<SIMD>(),
        simd(user)
        {
            assert(simd);
            assert(0==simd->quantity());
            simd->withhold();
        }

        
    }
}
