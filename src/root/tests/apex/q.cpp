#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_q)
{
    Core::Rand ran;

    { apq q; std::cerr << q << std::endl; }

    {
        for(size_t iter=0;iter<10;++iter)
        {
            const apz numer(ran, ran.in<size_t>(0,8) );
            const apn denom(ran, ran.in<size_t>(1,8) );
            const apq q(numer,denom);

            std::cerr << numer << "/" << denom << " => " << q << std::endl;
        }
    }


    {
        apq a(3,2), b(6,4); Y_CHECK(a==b);
    }

    {
        const integer_t i = -7;
        const Integer   I = i;
        const apq a(-14,2);
        Y_CHECK(a==I); Y_CHECK(a==i);
        Y_CHECK(I==a); Y_CHECK(i==a);
    }

    {
        const apq zero;
        const apq half(1,2);
        const apq third(1,3);
        const apq minus_fourth(-1,4);
        const apq minus_two_third(-2,3);

        Y_CHECK( __Zero__ == apq::Cmp(zero,zero)   );
        Y_CHECK( __Zero__ == apq::Cmp(third,third) );
        Y_CHECK( __Zero__ == apq::Cmp(minus_fourth,minus_fourth) );

        Y_CHECK( Positive == apq::Cmp(zero,minus_two_third) );
        Y_CHECK( Negative == apq::Cmp(minus_fourth,zero) );
        Y_CHECK( Positive == apq::Cmp(half,minus_two_third) );
        Y_CHECK( Negative == apq::Cmp(minus_fourth,third) );

        Y_CHECK( Positive == apq::Cmp(half,third) );
        Y_CHECK( Positive == apq::Cmp(minus_fourth,minus_two_third) );

        Y_CHECK( Negative == apq::Cmp(third,half) );
        Y_CHECK( Negative == apq::Cmp(minus_two_third,minus_fourth) );
    }


    {
        const apq q0;
        const apz z0;
        const apz z1 = 1;
        const apz zm1 = -1;
        const apq q1  = 1;
        const apq qm1 = -1;
        const apq q1_2(1,2), qm1_2(-1,2), q3_2(3,2), qm3_2(-3,2);


        Y_CHECK( __Zero__ == apq::Cmp(q0,z0) );
        Y_CHECK( __Zero__ == apq::Cmp(z0,q0) );
        Y_CHECK( __Zero__ == apq::Cmp(q1,z1) );
        Y_CHECK( __Zero__ == apq::Cmp(z1,q1) );

        Y_CHECK( __Zero__ == apq::Cmp(qm1,zm1) );
        Y_CHECK( __Zero__ == apq::Cmp(zm1,qm1) );

        Y_CHECK( Positive == apq::Cmp(q1_2,z0)   );
        Y_CHECK( Positive == apq::Cmp(q3_2,z1)   );
        Y_CHECK( Negative == apq::Cmp(qm3_2,zm1) );
        Y_CHECK( Negative == apq::Cmp(qm1_2,z0)  );
        Y_CHECK( Positive == apq::Cmp(q1_2,zm1)   );

    }

    {
        const apq q0, q1_2(1,2), qm1_2(-1,2), q3_2(3,2);
        const apn n0, n1(1);

        Y_CHECK( __Zero__ == apq::Cmp(q0,n0) );
        Y_CHECK( Positive == apq::Cmp(q1_2,n0) );
        Y_CHECK( Positive == apq::Cmp(q3_2,n1) );
        Y_CHECK( Negative == apq::Cmp(q1_2,n1) );
        Y_CHECK( Negative == apq::Cmp(qm1_2,n0) );
        Y_CHECK( Negative == apq::Cmp(qm1_2,n1) );

    }


}
Y_UDONE()


