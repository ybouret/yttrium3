#include "y/apex/n/modular.hpp"
#include "y/calculus/prime/next.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    static inline uint64_t GetPrime( Core::Rand & ran )
    {
        return Prime::Next( ran.in<uint64_t>(10,1000) );
    }
}

Y_UTEST(apex_rsa)
{

    Core::Rand ran;

    {
        std::cerr << "-- Modular Inv" << std::endl;
        for(size_t in=1;in<=40;in += 1+ran.leq<size_t>(8))
        {
            for(size_t ia=1;ia<=10;++ia)
            {
                for(size_t iter=0;iter<32;++iter)
                {
                    apn        n(ran,in);
                    const apn  a(ran,ia);
                    while( a>=n || 1 != apn::GCD(n,a) ) ++n;
                    const apn b = Apex::Modular::Inv(a,n);
                    const apn r = (a*b) % n;
                    Y_ASSERT(1==r);
                }
            }
        }

    }


    {
        std::cerr << "-- RSA" << std::endl;
        const apn p   = GetPrime(ran);
        apn       q   = GetPrime(ran); while(q==p) q = GetPrime(ran);
        const apn n   = p*q;
        const apn lam = apn::LCM(p-1,q-1);
        std::cerr << "p   = " << p   << std::endl;
        std::cerr << "q   = " << q   << std::endl;
        std::cerr << "n   = " << n   << std::endl;
        std::cerr << "lam = " << lam << std::endl;
        const uint64_t l = lam.cast<uint64_t>("lam",0);
        std::cerr << "l   = " << l   << std::endl;
        apn e = 3;
        while( 1 != apn::GCD(e,lam) )
        {
            e += 2;
        }
        std::cerr << "e=" << e << std::endl;
        const apn d = Apex::Modular::Inv(e,lam);
        std::cerr << "d=" << d << std::endl;

        for(apn m=0;m<n;++m)
        {
            (std::cerr << std::setw(10) << m.toHex()).flush();
            const apn c = Apex::Modular::Exp(m,e,n);
            (std::cerr << " => " << std::setw(10) << c.toHex()).flush();
            const apn r = Apex::Modular::Exp(c,d,n);
            (std::cerr << " => " << std::setw(10) << r.toHex()).flush();
            std::cerr << std::endl;
            Y_ASSERT(r==m);
        }
    }

}
Y_UDONE()

