//! \file

#ifndef Y_MKL_Tao_Device_Included
#define Y_MKL_Tao_Device_Included 1

#include "y/concurrent/api/engine.hpp"
#include "y/concurrent/splitting/tiles1d.hpp"
#include "y/concurrent/splitting/tiles2d.hpp"
#include "y/concurrent/splitting/udts.hpp"

namespace Yttrium
{
    namespace Tao
    {



        class Device : public Concurrent::Engine
        {
        public:
            explicit Device(const Concurrent::Engine &);
            virtual ~Device() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Device);
        };
    }
}

#endif // !Y_MKL_Tao_Device_Included
