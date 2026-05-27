
#include "y/apex/n/modular.hpp"
#include "y/calculus/prime/next.hpp"
#include "y/calculus/prime/prev.hpp"
#include "y/calculus/isqrt.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    T scatter(const T &top)
    {
        std::cerr << "top=" << top << std::endl;
        const T s = IntegerSquareRoot(top);
        std::cerr << "s = " << s << std::endl;

        Y_ASSERT(s>2);
        apn       p = Prime::Next(s+1);
        const apn q = Prime::Prev(s-1);
        std::cerr << "q = " << q << std::endl;
        apn n = p*q;
        while(n<top)
        {
            ++p;
            p = Prime::Next( p.cast<T>("p",0) );
            n = p*q;
        }
        std::cerr << "p = " << p << std::endl;
        std::cerr << "n   = " << n << std::endl;
        const apn lam = apn::LCM(p-1,q-1);
        std::cerr << "lam = " << lam << std::endl;
        apn e = 3;
        while( ! apn::GCD(e,lam).is1() )
        {
            e += 2;
        }
        std::cerr << "e=" << e << std::endl;
        const apn d = Apex::Modular::Inv(e,lam);
        std::cerr << "d=" << d << std::endl;

        for(size_t m=0;m<n;++m)
        {
            const apn    c = Apex::Modular::Exp(m,e,n);
            const size_t j = c.cast<T>("c",0);
            if(j<=top)
            {
            }
        }


        return n.cast<T>("n",0);
    }
}

#include "y/ascii/convert.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/decimal.hpp"

Y_UTEST(apex_scatter)
{
    uint32_t   top = 6000;
    if(argc>1) top = ASCII::Convert::To<uint32_t>(argv[1],"top",0);
    scatter( top );


    if(0);

    {
        OutputFile fp("apex-scatter.dat");
        for(size_t i=10;i<=top;++i)
        {
            fp("%s %s\n", Decimal(i).c_str(), Decimal( scatter(i) ).c_str() );
        }
    }


}
Y_UDONE()
