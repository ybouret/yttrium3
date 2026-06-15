
//! \file

#ifndef Y_Random_Uniform32_Included
#define Y_Random_Uniform32_Included 1

#include "y/random/coin-flip.hpp"

namespace Yttrium
{
    namespace Random
    {

        class Uniform32
        {
        public:
            explicit Uniform32(const uint32_t umax) noexcept;
            virtual ~Uniform32() noexcept;

            virtual uint32_t next32() noexcept = 0;

            double operator()() noexcept;

            
            template <typename T> T to() noexcept;


            const uint32_t max32;
            const double   denom;
        private:
            Y_Disable_Copy_And_Assign(Uniform32);
        };

    }
}

#endif // !Y_Random_Uniform32_Included
