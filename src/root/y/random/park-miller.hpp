
//! \file

#ifndef Y_Random_Park_Miller_Included
#define Y_Random_Park_Miller_Included 1

#include "y/random/uniform32.hpp"

namespace Yttrium
{
    namespace Random
    {
        class ParkMiller : public Uniform32
        {
        public:

            explicit ParkMiller();
            virtual ~ParkMiller() noexcept;

            virtual uint32_t next32() noexcept;

        private:
            Y_Disable_Copy_And_Assign(ParkMiller);
            long seed;
        };
    }

}

#endif // !Y_Random_Park_Miller_Included
