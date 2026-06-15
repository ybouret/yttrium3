
#include "y/random/uniform32.hpp"
#include <iostream>

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
            //std::cerr << "max32=" << max32 << std::endl;
            //std::cerr << "denom=" << denom << std::endl;
        }


        double Uniform32:: operator()() noexcept
        {
            static const double half = 0.5;
            return ( half + (double)next32()   )/denom;
        }

        template <> double       Uniform32:: to<double>()       noexcept { return (*this)(); }
        template <> float        Uniform32:: to<float>()        noexcept { return (float)((*this)()); }
        template <> long double  Uniform32:: to<long double>()  noexcept { return (long double)((*this)()); }

        template <>
        uint32_t Uniform32:: to<uint32_t>() noexcept { return next32(); }

        template <>
        uint16_t Uniform32:: to<uint16_t>() noexcept { return (uint16_t)next32(); }


        template <>
        uint8_t Uniform32:: to<uint8_t>() noexcept { return (uint8_t)next32(); }


        template <>
        uint64_t Uniform32:: to<uint64_t>() noexcept
        {
            const uint64_t lo = next32();
            const uint64_t hi = next32();
            return lo | (hi<<32);
        }

    }

}


