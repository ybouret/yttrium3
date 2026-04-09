
#include "y/calculus/split-word.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        uint8_t * SplitWord:: Make<uint8_t>::From(uint16_t &x) noexcept
        {
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[2] = { (uint8_t) x, (uint8_t)(x>>8) };
            p[0]  = u[0];
            p[1]  = u[1];
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint32_t &x) noexcept
        {
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[4] = { (uint8_t) x, (uint8_t)(x>>8), (uint8_t)(x>>16), (uint8_t)(x>>24) };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint64_t &x ) noexcept
        {
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


        uint16_t * SplitWord:: Make<uint16_t>::From(uint32_t &x) noexcept
        {
            uint16_t * const p    = (uint16_t *) &x;
            const uint16_t   u[2] = { (uint16_t) x, (uint16_t) (x>>16) };
            p[0]  = u[0];
            p[1]  = u[1];
            return p;
        }

        uint16_t * SplitWord:: Make<uint16_t>::From(uint64_t &x) noexcept
        {
            uint16_t * const p    = (uint16_t *) &x;
            const uint16_t   u[4] = { (uint16_t) x, (uint16_t) (x>>16), (uint16_t) (x>>32), (uint16_t) (x>>48) };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            return p;
        }

        uint32_t * SplitWord:: Make<uint32_t>::From(uint64_t &x) noexcept
        {
            uint32_t * const p    = (uint32_t *) &x;
            const uint32_t   u[2] = { (uint32_t) x, (uint32_t) (x>>32) };
            p[0]  = u[0];
            p[1]  = u[1];
            return p;
        }
    }

}
