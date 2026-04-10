#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_n)
{
    Core::Rand ran;

    {
        const uint64_t n = 0x12345;
        apn            N = n;
        std::cerr << Hexadecimal(n,Concise) << " => " << N << std::endl;
    }

    (std::cerr << "-- Test Cmp 64-bits " << std::endl).flush();
    for(size_t i=0;i<=64;++i)
    {
        for(size_t j=0;j<=64;++j)
        {
            for(size_t k=0;k<16;++k)
            {
                const natural_t lhs = ran.gen<natural_t>(i);
                const natural_t rhs = ran.gen<natural_t>(j);
                const SignType  cmp = Sign::Of(lhs,rhs);
                const apn       L   = lhs;
                const apn       R   = rhs;
                Y_ASSERT( Natural::Cmp(L,R)   == cmp );
                Y_ASSERT( Natural::Cmp(L,rhs) == cmp );
                Y_ASSERT( Natural::Cmp(lhs,R) == cmp );
            }

        }
    }

    (std::cerr << "-- Test Add 64-bits " << std::endl).flush();
    for(size_t i=0;i<=63;++i)
    {
        for(size_t j=0;j<=63;++j)
        {
            {
                const natural_t lhs = ran.gen<natural_t>(i);
                const natural_t rhs = ran.gen<natural_t>(j);
                const natural_t sum = lhs + rhs;
                const apn       L   = lhs;
                const apn       R   = rhs;
                { const apn     S   = L + R;   Y_ASSERT(S==sum); }
                { const apn     S   = lhs + R; Y_ASSERT(S==sum); }
                { const apn     S   = L + rhs; Y_ASSERT(S==sum); }
                { apn S = L; S += R;  Y_ASSERT(S==sum); }
                { apn S = L; S += rhs; Y_ASSERT(S==sum); }

            }
        }
    }

    for(apn i=0;i<=20;++i) std::cerr << i << ' ';
    std::cerr << std::endl;
    for(apn i=0;i<=20;i++) std::cerr << i << ' ';
    std::cerr << std::endl;

}
Y_UDONE()

