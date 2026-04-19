#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_q)
{
    Core::Rand ran;

    std::cerr << std::endl << "-- reduction" << std::endl;
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


    std::cerr << std::endl << "-- equalities" << std::endl;
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

    std::cerr << std::endl << "-- comparisons" << std::endl;
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

    {
        const apq       q0, q1 = 1, qm1 = -1;
        const integer_t i0 = 0, i1 = 1, im1 = -1;
        const apq       q1_2(1,2), qm1_2(-1,2);
        const apq       q3_2(3,2), qm3_2(-3,2);


        Y_CHECK( __Zero__ == apq::Cmp(q0,i0) );
        Y_CHECK( __Zero__ == apq::Cmp(q1,i1) );
        Y_CHECK( __Zero__ == apq::Cmp(qm1,im1) );

        Y_CHECK( Positive == apq::Cmp(q1_2,i0) );
        Y_CHECK( Positive == apq::Cmp(qm1_2,im1) );
        Y_CHECK( Negative == apq::Cmp(qm1_2,i0) );
        Y_CHECK( Positive == apq::Cmp(q3_2,i1) );
        Y_CHECK( Negative == apq::Cmp(qm3_2,i1) );
        Y_CHECK( Negative == apq::Cmp(qm1_2,i1) );
    }


    std::cerr << std::endl << "-- add/sub" << std::endl;
    for(size_t iter=0;iter<1024;++iter)
    {
        {
            const apq lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apq rhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apq sum = lhs + rhs;
            //std::cerr << lhs << " + " << rhs << " = " << sum << std::endl;
            Y_ASSERT(rhs+lhs==sum);
            Y_ASSERT(sum - lhs == rhs);
            Y_ASSERT(sum - rhs == lhs);
            apq S = lhs; S += rhs; Y_ASSERT(sum == S);
            S -= rhs;              Y_ASSERT(lhs == S);
        }

        {
            const apq lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apz rhs(ran,ran.in<size_t>(0,8));
            const apq sum = lhs + rhs;
            Y_ASSERT(rhs+lhs==sum);
            Y_ASSERT(sum - lhs == rhs);
            Y_ASSERT(sum - rhs == lhs);
            apq S = lhs; S += rhs; Y_ASSERT(sum == S);
            S -= rhs;              Y_ASSERT(lhs == S);
        }

        {
            const apq lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apn rhs(ran,ran.in<size_t>(0,8));
            const apq sum = lhs + rhs;
            Y_ASSERT(rhs+lhs==sum);
            Y_ASSERT(sum - lhs == rhs); // with conversion!
            Y_ASSERT(sum - rhs == lhs);
            apq S = lhs; S += rhs; Y_ASSERT(sum == S);
            S -= rhs;              Y_ASSERT(lhs == S);
        }


        {
            const apq       lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const integer_t rhs = ran.in<integer_t>(-100,100);
            const apq sum = lhs + rhs;
            Y_ASSERT(rhs+lhs==sum);
            Y_ASSERT(sum - lhs == rhs); // with conversion!
            Y_ASSERT(sum - rhs == lhs);
            apq S = lhs; S += rhs; Y_ASSERT(sum == S);
            S -= rhs;              Y_ASSERT(lhs == S);
        }

    }

    for(Rational q(-10,3); q <= 5; ++q) std::cerr << ' ' << q;
    std::cerr << std::endl;
    for(Rational q(-10,3); q <= 5; q++) std::cerr << ' ' << q;
    std::cerr << std::endl;

    for(Rational q(10,3); q >= -5; --q) std::cerr << ' ' << q;
    std::cerr << std::endl;
    for(Rational q(10,3); q >= -5; q--) std::cerr << ' ' << q;
    std::cerr << std::endl;


    std::cerr << std::endl << "-- mul/div" << std::endl;
    for(size_t iter=0;iter<2048;++iter)
    {
        {
            const apq lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apq rhs(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );
            const apq rho = lhs / rhs;
            const apq org = rho * rhs;
            Y_ASSERT(org==lhs);
        }

        {
            const apq lhs(ran,ran.in<size_t>(0,12), ran.in<size_t>(1,12) );
            const apz rhs(ran,ran.in<size_t>(1,12));
            const apq prod = lhs * rhs;
            Y_ASSERT(rhs*lhs==prod);
            Y_ASSERT(prod/rhs==lhs);
        }

        {
            const apz z(ran,ran.in<size_t>(1,12));
            const apq q = z;
            const apq x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );
            Y_ASSERT(q/x==z/x);
        }

        {
            const integer_t z = ran.in<integer_t>(-1000,1000);
            const apq       q = z;
            const apq       x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );

            const apq prod = q * x;
            Y_ASSERT( z * x == prod);
            Y_ASSERT( x * z == prod);
        }

        {
            integer_t z = ran.in<integer_t>(-1000,1000);
            while(!z)
                z = ran.in<integer_t>(-1000,1000);
            const apq q = z;
            const apq x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );

            const apq rho = x/q;
            Y_ASSERT( x/z == rho);
        }

        {
            const integer_t z = ran.in<integer_t>(-1000,1000);
            const apq       q = z;
            const apq       x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );

            const apq rho = q / x;
            Y_ASSERT( z / x == rho);
        }



        {
            const apn n = ran.in<natural_t>(0,1000);
            const apq q = n;
            const apq x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );
            const apq prod = q * x;
            Y_ASSERT( n * x == prod);
            Y_ASSERT( x * n == prod);
        }


        {
            const apn n = ran.in<natural_t>(1,1000);
            const apq q = n;
            const apq x(ran,ran.in<size_t>(1,12), ran.in<size_t>(1,12) );
            const apq rho = x/q;
            Y_ASSERT(x/n == rho);
        }



    }
}
Y_UDONE()


