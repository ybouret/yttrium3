#include "y/random/park-miller.hpp"
#include "y/random/seed64.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Random
    {
        ParkMiller:: ~ParkMiller() noexcept
        {
        }


#define IA   16807
#define IM   2147483647
#define AMf (1.0f/(float)IM)
#define AMd (1.0/(double)IM)
#define AMl (1.0L/(long double)IM)
#define IQ   127773
#define IR   2836
#define MASK 123459876

        namespace
        {
            static inline
            long ParkMillerSeed() noexcept
            {
                static const uint64_t LMAX = IM; //(uint64_t) IntegerFor<long>::Maximum;
                const        uint64_t seed = Seed64::Get64();
                return (long) (seed%LMAX);
            }

        }

        ParkMiller:: ParkMiller()  :
        Uniform32(IM-1),
        seed( ParkMillerSeed() )
        {
        }

        uint32_t ParkMiller:: next32() noexcept
        {

            seed ^= MASK;
            const long k=(seed)/IQ;
            seed=IA*(seed-k*IQ)-IR*k;
            if (seed < 0) seed += IM;
            assert(seed>=0);
            assert(seed<IM);
            seed ^= MASK;

            return (uint32_t) seed;
        }

    }
}

