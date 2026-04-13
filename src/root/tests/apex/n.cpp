#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/swap.hpp"
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
            for(size_t k=0;k<16;++k)
            {
                const natural_t lhs = ran.gen<natural_t>(i);
                const natural_t rhs = ran.gen<natural_t>(j);
                const natural_t sum = lhs + rhs;
                const apn       L   = lhs;
                const apn       R   = rhs;
                { const apn     S   = L + R;   Y_ASSERT(S==sum); }
                { const apn     S   = lhs + R; Y_ASSERT(S==sum); }
                { const apn     S   = L + rhs; Y_ASSERT(S==sum); }
                { apn S = L; S += R;   Y_ASSERT(S==sum); }
                { apn S = L; S += rhs; Y_ASSERT(S==sum); }

            }
        }
    }

    for(apn i=0;i<=20;++i) std::cerr << i << ' ';
    std::cerr << std::endl;
    for(apn i=0;i<=20;i++) std::cerr << i << ' ';
    std::cerr << std::endl;


    (std::cerr << "-- Test Sub 64-bits " << std::endl).flush();
    for(size_t i=0;i<=64;++i)
    {
        for(size_t j=0;j<=i;++j)
        {
            for(size_t k=0;k<16;++k)
            {
                natural_t lhs = ran.gen<natural_t>(i);
                natural_t rhs = ran.gen<natural_t>(j);
                if(lhs<rhs) Swap(lhs,rhs);
                const natural_t dif = lhs - rhs;
                const apn       L   = lhs;
                const apn       R   = rhs;

                { const apn     D   = L   - R; Y_ASSERT(D==dif); }
                { const apn     D   = lhs - R; Y_ASSERT(D==dif); }
                { const apn     D   = L - rhs; Y_ASSERT(D==dif); }
                { apn D = L; D -= R;   Y_ASSERT(D==dif); }
                { apn D = L; D -= rhs; Y_ASSERT(D==dif); }


            }
        }
    }

    for(apn i=20;i>0;--i) std::cerr << i << ' ';
    std::cerr << std::endl;
    for(apn i=20;i>0;i--) std::cerr << i << ' ';
    std::cerr << std::endl;


    (std::cerr << "-- Test Mul 64-bits " << std::endl).flush();
    for(size_t i=0;i<=32;++i)
    {
        for(size_t j=0;j<=32;++j)
        {
            for(size_t k=0;k<16;++k)
            {
                const natural_t lhs  = ran.gen<natural_t>(i);
                const natural_t rhs  = ran.gen<natural_t>(j);
                const natural_t prod = lhs * rhs;
                const apn       L   = lhs;
                const apn       R   = rhs;
                { const apn     P   = L   * R; Y_ASSERT(P==prod); }
                { const apn     P   = lhs * R; Y_ASSERT(P==prod); }
                { const apn     P   = L * rhs; Y_ASSERT(P==prod); }
                { apn P = L; P *= R;           Y_ASSERT(P==prod);  }
                { apn P = L; P *= rhs;         Y_ASSERT(P==prod);  }

            }
        }
    }

    (std::cerr << "-- Test Bits " << std::endl).flush();
    {
        for(size_t p=0;p<=40;++p)
        {
            apn n(TwoToThePowerOf,p);
            std::cerr << n << std::endl;
            while(n>0)
            {
                std::cerr << n.shr() << std::endl;
            }
        }
        {
            apn n = 1;
            std::cerr << n << std::endl;
            for(size_t p=2;p<=40;++p)
            {
                std::cerr << n.shl() << std::endl;
            }
        }
    }


    (std::cerr << "-- Test SHR/SHL 64-bits " << std::endl).flush();
    {

        apn n(ran,10);
        std::cerr << n << std::endl;
        size_t total = 0;

    }




    (std::cerr << "-- Test Div 64-bits " << std::endl).flush();
    {

        std::cerr << '[';
        for(size_t i=0;i<=64;++i)
        {
            (std::cerr << '.').flush();
            for(size_t j=1;j<=64;++j)
            {
                for(size_t k=0;k<4;++k)
                {
                    const natural_t lhs  = ran.gen<natural_t>(i);
                    const natural_t rhs  = ran.gen<natural_t>(j);
                    const natural_t quot = lhs/rhs;
                    const natural_t rem  = lhs%rhs;
                    const apn       L    = lhs;
                    const apn       R    = rhs;
                    {
                        apn             Quot,Rem;
                        Natural::Division(0,0,L,R);
                        {
                            Natural::Division(&Quot,0,L,R);
                            Y_ASSERT(quot == Quot);
                        }

                        {
                            Natural::Division(0,&Rem,L,R);
                            Y_ASSERT(rem == Rem);
                        }

                        Quot = 0;
                        Rem  = 0;

                        {
                            Natural::Division(&Quot,&Rem,L,R);
                            Y_ASSERT(quot == Quot);
                            Y_ASSERT(rem == Rem);
                        }
                    }

                    { const apn Quot = L/R;       Y_ASSERT(Quot==quot); }
                    { const apn Quot = L/rhs;     Y_ASSERT(Quot==quot); }
                    { const apn Quot = lhs/R;     Y_ASSERT(Quot==quot); }
                    {  apn Quot = L; Quot /= R;   Y_ASSERT(Quot==quot); }
                    {  apn Quot = L; Quot /= rhs; Y_ASSERT(Quot==quot); }

                    { const apn Rem = L%R;       Y_ASSERT(Rem==rem); }
                    { const apn Rem = L%rhs;     Y_ASSERT(Rem==rem); }
                    { const apn Rem = lhs%R;     Y_ASSERT(Rem==rem); }
                    {  apn Rem = L; Rem %= R;    Y_ASSERT(Rem==rem); }
                    {  apn Rem = L; Rem %= rhs;  Y_ASSERT(Rem==rem); }

                }
            }
        }
        std::cerr << ']' << std::endl;
    }




}
Y_UDONE()

