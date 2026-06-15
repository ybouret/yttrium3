
#include "y/random/uniform32.hpp"

namespace Yttrium
{
    namespace Random
    {

        Uniform32:: ~Uniform32() noexcept
        {
        }

        static const uint32_t Max32 = IntegerFor<uint32_t>::Maximum;



        Uniform32:: Uniform32(const uint32_t umax) noexcept :
        max32(umax),
        denom( max32 < Max32 ? (double)(max32+1) : 4294967296.0)
        {
        }


        double Uniform32:: operator()() noexcept
        {
            static const double half = 0.5;
            return ( half + (double)next32()   )/denom;
        }

    }

}


