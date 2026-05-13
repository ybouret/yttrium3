#include "y/libc/pq/api.h"
#include "y/libc/block/zero.h"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/type/sign.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline int cmp(const void * const lhs, const void * const rhs, void * const) noexcept
    {
        const T &L = *(const T *)lhs;
        const T &R = *(const T *)rhs;
        return Sign::Of(L,R);
    }

    template <typename T, size_t N> static inline
    void testPQ(Core::Rand &ran)
    {

        T data[N];
        Y_BZero(data);
        size_t n = 0;

        while(n<N)
        {
            const T x = ran.in<T>(0,100);
            data[n++] = x;
            Core::Display(std::cerr,data,n) << " => ";
            Yttrium_PQ_Balance(data,n,sizeof(T), cmp<T>, 0);
            Core::Display(std::cerr,data,n) << std::endl;
        }

    }
}

Y_UTEST(container_pq)
{
    Core::Rand ran;
    testPQ<int,10>(ran);
    testPQ<uint16_t,16>(ran);

}
Y_UDONE()
