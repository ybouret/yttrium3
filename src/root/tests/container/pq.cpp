#include "y/libc/pq/api.h"
#include "y/libc/block/zero.h"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/type/sign.hpp"
#include "y/core/display.hpp"
#include "y/libc/sort.h"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline
    int cmp(const void * const lhs, const void * const rhs, void * const) noexcept
    {
        const T &L = *(const T *)lhs;
        const T &R = *(const T *)rhs;
        const int res = Sign::Of(L,R);
        return res;
    }

    template <typename T, size_t N> static inline
    void testPQ(Core::Rand &ran)
    {

        T data[N];
        T temp[N];

        for(size_t iter=0;iter<4;++iter)
        {
            Y_BZero(data);
            Y_BZero(temp);
            size_t n = 0;
            std::cerr << "-- push" << std::endl;
            while(n<N)
            {
                const T x = ran.in<T>(0,100);
                data[n] = x;
                temp[n] = x;
                ++n;
                std::cerr << "[+] " << std::setw(3) << x << " : ";
                Core::Display(std::cerr,data,n) << " => ";
                Yttrium_PQ_Push_Balance(data,n,sizeof(T), cmp<T>, 0);
                Core::Display(std::cerr,data,n) << std::endl;
            }

            {
                T rra = 0;
                Yttrium_Sort(temp,n,sizeof(T),cmp<T>,0,&rra);
            }



            std::cerr << "-- pull" << std::endl;
            Core::Display(std::cerr,temp,n) << std::endl;
            size_t i = 0;
            while(n>0)
            {
                Y_ASSERT(data[0]==temp[i]);
                std::cerr << data[0] << " => ";
                Yttrium_PQ_Pull_Balance(data,--n,sizeof(T), cmp<T>, 0);
                Core::Display(std::cerr,data,n) << std::endl;
                ++i;
            }

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
