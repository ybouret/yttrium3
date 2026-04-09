
#include "y/calculus/split-word.hpp"
#include "y/calculus/required-bytes.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        uint8_t * SplitWord:: Make<uint8_t>::From(uint16_t &x, size_t &n) noexcept
        {
            n                 = RequiredBytes::For(x);
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[2] = { (uint8_t) x, (uint8_t)(x>>8) };
            p[0]  = u[0];
            p[1]  = u[1];
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint32_t &x, size_t &n) noexcept
        {
            n                 = RequiredBytes::For(x);
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[4] = { (uint8_t) x, (uint8_t)(x>>8), (uint8_t)(x>>16), (uint8_t)(x>>24) };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint64_t &x, size_t &n) noexcept
        {
            n                 = RequiredBytes::For(x);
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[8] =
            {
                (uint8_t) x,
                (uint8_t)(x>>8),
                (uint8_t)(x>>16),
                (uint8_t)(x>>24),
                (uint8_t)(x>>32),
                (uint8_t)(x>>40),
                (uint8_t)(x>>48),
                (uint8_t)(x>>56),
            };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            p[4]  = u[4];
            p[5]  = u[5];
            p[6]  = u[6];
            p[7]  = u[7];
            return p;
        }

    }

}
