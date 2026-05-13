#include "y/container/ordered/static-prio-q.hpp"
#include "y/libc/block/zero.h"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/type/sign.hpp"
#include "y/core/display.hpp"
#include "y/libc/sort.h"
#include "y/apex/rational.hpp"
#include "y/calculus/alignment.hpp"

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

    template <size_t N>
    static inline void testPrioQ(Core::Rand &ran)
    {
        std::cerr << "-- prioQ with " << N << " items" << std::endl;
        void * wksp[ Alignment::WordsGEQ<N*sizeof(apz)>::Count ];
        Y_BZero(wksp);

        PrioQ<apz> pq(wksp,N);
        std::cerr << "-- populating" << std::endl;
        while(pq.size<pq.capacity)
        {
            const apz z(ran,ran.in<size_t>(0,10));
            pq.push(Sign::Increasing<apz>,z);
            std::cerr << std::setw(10) << pq.peek() << " : " << pq << std::endl;
        }
        std::cerr << "-- pulling" << std::endl;
        while(pq.size)
        {
            const apz z = pq.pull(Sign::Increasing<apz>);
            std::cerr << std::setw(10) << z << " : " << pq << std::endl;
        }
    }




}

Y_UTEST(container_pq)
{
    Core::Rand ran;
    testPQ<int,10>(ran);
    testPQ<uint16_t,16>(ran);

    testPrioQ<10>(ran);

    {
        StaticPrioQ<apn,10> spq;
        std::cerr << "-- populating static prioQ" << std::endl;
        while(spq.size()<spq.Capacity)
        {
            const apn n(ran,ran.in<size_t>(5,10));
            spq.push(n);
            std::cerr << std::setw(10) << spq.peek() << " : " << spq << std::endl;
        }
        std::cerr << "-- pulling" << std::endl;
        while(spq.size())
        {
            const apn n = spq.pull();
            std::cerr << std::setw(10) << n << " : " << spq << std::endl;
        }

    }


}
Y_UDONE()
