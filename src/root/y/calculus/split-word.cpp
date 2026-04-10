
#include "y/calculus/split-word.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Calculus
    {
        void SplitWord:: Expand(uint8_t * const target, const uint16_t &source) noexcept
        {
            const uint8_t u[2] = { (uint8_t)(source), (uint8_t)(source>>8) };
            target[0]   = u[0];
            target[1]   = u[1];
        }

        void SplitWord:: Expand(uint8_t * const target, const uint32_t &source) noexcept
        {
            const uint8_t u[4] = { (uint8_t)(source), (uint8_t)(source>>8), (uint8_t)(source>>16), (uint8_t)(source>>24) };
            target[0]   = u[0];
            target[1]   = u[1];
            target[2]   = u[2];
            target[3]   = u[3];
        }

        void SplitWord:: Expand(uint8_t * const target, const uint64_t &source) noexcept
        {
            const uint8_t u[8] =
            {
                (uint8_t)(source),     (uint8_t)(source>>8),  (uint8_t)(source>>16), (uint8_t)(source>>24),
                (uint8_t)(source>>32), (uint8_t)(source>>40), (uint8_t)(source>>48), (uint8_t)(source>>56)
            };
            target[0]   = u[0];
            target[1]   = u[1];
            target[2]   = u[2];
            target[3]   = u[3];
            target[4]   = u[4];
            target[5]   = u[5];
            target[6]   = u[6];
            target[7]   = u[7];
        }

        void SplitWord:: Expand(uint16_t * const target, const uint32_t &source) noexcept
        {
            const uint16_t u[2] = { (uint16_t)(source), (uint16_t)(source>>16) };
            target[0]   = u[0];
            target[1]   = u[1];
        }

        void SplitWord:: Expand(uint16_t * const target, const uint64_t &source) noexcept
        {
            const uint16_t u[4] =
            {
                (uint16_t)(source),
                (uint16_t)(source>>16),
                (uint16_t)(source>>32),
                (uint16_t)(source>>48)
            };
            target[0]   = u[0];
            target[1]   = u[1];
            target[2]   = u[2];
            target[3]   = u[3];
        }

        void SplitWord:: Expand(uint32_t * const target, const uint64_t &source) noexcept
        {
            const uint32_t u[2] = { (uint32_t)(source), (uint32_t)(source>>32) };
            target[0]   = u[0];
            target[1]   = u[1];
        }


    }

    namespace Calculus
    {
        void SplitWord:: Gather(uint16_t & target, const uint8_t * const source) noexcept
        {
            assert(source);
            const uint16_t u[2] = { source[0], source[1] };
            target = (uint16_t)(u[0] | (u[1] << 8));
        }

        void SplitWord:: Gather(uint32_t & target, const uint8_t * const source) noexcept
        {
            assert(source);
            const uint32_t u[4] = { source[0], source[1], source[2], source[3] };
            target = u[0] | (u[1]<<8) | (u[2]<<16) | (u[3]<<24);
        }

        void SplitWord:: Gather(uint64_t & target, const uint8_t * const source) noexcept
        {
            assert(source);
            const uint64_t u[8] = { source[0], source[1], source[2], source[3], source[4], source[5], source[6], source[7] };
            target =
            u[0]       |
            (u[1]<<8)  |
            (u[2]<<16) |
            (u[3]<<24) |
            (u[4]<<32) |
            (u[5]<<40) |
            (u[6]<<48) |
            (u[7]<<56);
        }

        void SplitWord:: Gather(uint32_t & target, const uint16_t * const source) noexcept
        {
            assert(source);
            const uint32_t u[2] = { source[0], source[1] };
            target = u[0] | (u[1]<<16);
        }

        void SplitWord:: Gather(uint64_t & target, const uint16_t * const source) noexcept
        {
            assert(source);
            const uint64_t u[4] = { source[0], source[1], source[2], source[3] };
            target = u[0] | (u[1]<<16) | (u[2]<<32) | (u[3]<<48);
        }

        void SplitWord:: Gather(uint64_t & target, const uint32_t * const source) noexcept
        {
            assert(source);
            const uint64_t u[2] = { source[0], source[1] };
            target = u[0] | (u[1]<<32);
        }



    }

    namespace Calculus
    {

        namespace
        {
            template <typename T,size_t N> struct SplitCount
            {
                static inline
                size_t For(const T u[]) noexcept
                {
                    return u[N-1] ? N : SplitCount<T,N-1>::For(u);
                }
            };

            template <typename T> struct SplitCount<T,0>
            {
                static inline size_t For(const T * const) noexcept { return 0; }
            };


        }
        uint8_t * SplitWord:: Make<uint8_t>::From(uint16_t &x, size_t &n) noexcept
        {
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[2] = { (uint8_t) x, (uint8_t)(x>>8) };
            p[0]  = u[0];
            p[1]  = u[1];
            n = SplitCount<uint8_t,Y_Static_Size(u)>::For(u);
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint32_t &x, size_t &n) noexcept
        {
            uint8_t * const p = (uint8_t *) &x;
            const uint8_t   u[4] = { (uint8_t) x, (uint8_t)(x>>8), (uint8_t)(x>>16), (uint8_t)(x>>24) };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            n = SplitCount<uint8_t,Y_Static_Size(u)>::For(u);
            return p;
        }


        uint8_t * SplitWord:: Make<uint8_t>::From(uint64_t &x, size_t &n) noexcept
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
            n = SplitCount<uint8_t,Y_Static_Size(u)>::For(u);
            return p;
        }


        uint16_t * SplitWord:: Make<uint16_t>::From(uint32_t &x, size_t &n) noexcept
        {
            uint16_t * const p    = (uint16_t *) &x;
            const uint16_t   u[2] = { (uint16_t) x, (uint16_t) (x>>16) };
            p[0]  = u[0];
            p[1]  = u[1];
            n = SplitCount<uint16_t,Y_Static_Size(u)>::For(u);
            return p;
        }

        uint16_t * SplitWord:: Make<uint16_t>::From(uint64_t &x, size_t &n) noexcept
        {
            uint16_t * const p    = (uint16_t *) &x;
            const uint16_t   u[4] = { (uint16_t) x, (uint16_t) (x>>16), (uint16_t) (x>>32), (uint16_t) (x>>48) };
            p[0]  = u[0];
            p[1]  = u[1];
            p[2]  = u[2];
            p[3]  = u[3];
            n = SplitCount<uint16_t,Y_Static_Size(u)>::For(u);
            return p;
        }

        uint32_t * SplitWord:: Make<uint32_t>::From(uint64_t &x,size_t &n) noexcept
        {
            uint32_t * const p    = (uint32_t *) &x;
            const uint32_t   u[2] = { (uint32_t) x, (uint32_t) (x>>32) };
            p[0]  = u[0];
            p[1]  = u[1];
            n = SplitCount<uint32_t,Y_Static_Size(u)>::For(u);
            return p;
        }
    }

}
