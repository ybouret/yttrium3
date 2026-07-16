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
        //______________________________________________________________________
        //
        //
        //
        //! Proxy acting as smart pointer to SIMD
        //
        //
        //______________________________________________________________________
        class Engine : public Proxy<SIMD>
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Engine(SIMD * const)   noexcept; //!< setup with new SIMD
            Engine(const Engine &) noexcept; //!< duplicate (shared copy)
            virtual ~Engine()      noexcept; //!< cleanup

        private:
            Y_Disable_Assign(Engine); //!< discarded
            Y_Proxy_Decl();           //!< helper
            SIMD * const simd;        //!< shared instance
        };

    }
}

#endif // !Y_Concurrent_Engine_Included

