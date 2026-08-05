
#include "y/random/bits.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Random
    {

        Bits:: ~Bits() noexcept
        {
        }

        static const uint32_t Max32 = IntegerFor<uint32_t>::Maximum;



        Bits:: Bits(const uint32_t umax) noexcept :
        max32(umax),
        denom( max32 < Max32 ? (double)(max32+1) : 4294967296.0)
        {
            //std::cerr << "max32=" << max32 << std::endl;
            //std::cerr << "denom=" << denom << std::endl;
        }


        double Bits:: operator()() noexcept
        {
            static const double half = 0.5;
            return ( half + (double)next32()   )/denom;
        }

        double Bits:: symm32() noexcept
        {
            const double u = (*this)();
            return 1.0 - (u+u);
        }

        template <> double       Bits:: to<double>()       noexcept { return (*this)(); }
        template <> float        Bits:: to<float>()        noexcept { return (float)((*this)()); }
        template <> long double  Bits:: to<long double>()  noexcept { return (long double)((*this)()); }

        template <> uint32_t Bits:: to<uint32_t>() noexcept { return next32(); }
        template <> uint16_t Bits:: to<uint16_t>() noexcept { return (uint16_t)next32(); }
        template <> uint8_t  Bits:: to<uint8_t>() noexcept { return (uint8_t)next32(); }


        template <>
        uint64_t Bits:: to<uint64_t>() noexcept
        {
            const uint64_t lo = next32();
            const uint64_t hi = next32();
            return lo | (hi<<32);
        }

        template <> double       Bits:: symm<double>()       noexcept { return               symm32(); }
        template <> float        Bits:: symm<float>()        noexcept { return (float)       symm32(); }
        template <> long double  Bits:: symm<long double>()  noexcept { return (long double) symm32(); }

    }

}


