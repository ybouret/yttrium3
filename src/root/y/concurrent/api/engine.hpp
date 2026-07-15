//! \file

#ifndef Y_Concurrent_Engine_Included
#define Y_Concurrent_Engine_Included 1


#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/thread/venue.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Engine : public Proxy<SIMD>
        {
        public:
            Engine(SIMD * const)   noexcept;
            Engine(const Engine &) noexcept;
            virtual ~Engine()      noexcept;
            
        private:
            Y_Disable_Assign(Engine);
            Y_Proxy_Decl();
            SIMD * const simd;
        };

    }
}

#endif // !Y_Concurrent_Engine_Included

