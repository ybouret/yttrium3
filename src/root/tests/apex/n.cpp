#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{
    static inline bool IsZero(const char c) noexcept { return '0' == c; }

}
Y_UTEST(apex_n)
{
    Core::Rand ran;

    std::cerr << "-- testing Factorial" << std::endl;
    for(natural_t n=0;n<=21;++n)
    {
        const apn f = apn::Factorial(n);
        std::cerr << std::setw(2) << n << "! = " << std::setw(20) << f << " #bits=" << f.bits() << std::endl;
    }
    
    std::cerr << "-- testing Comb" << std::endl;
    for(size_t n=0;n<=10;++n)
    {
        std::cerr << std::setw(2) << n << ":";
        for(size_t k=0;k<=n;++k) std::cerr << ' ' << apn::Comb(n,k);
        std::cerr << std::endl;
    }

    std::cerr << "-- testing add/sub" << std::endl;
    for(size_t k=0;k<1024;++k)
    {
        const apn lhs(ran,ran.in<size_t>(0,1000));
        const apn rhs(ran,ran.in<size_t>(0,1000));
        const apn sum = lhs + rhs;
        Y_ASSERT(sum-lhs==rhs);
        const apn cpy = +lhs;
    }

    std::cerr << "-- testing byte access" << std::endl;
    for(size_t iter=0;iter<32;++iter)
    {
        const apn n(ran,ran.in<size_t>(1,100));
        const String H = n.toHex();
        {
            const apn parsed = ASCII::Convert::ToAPN(H.c_str(),H.size());
            Y_ASSERT(parsed==n);
        }

        String       h;
        for(size_t i=n.bytes();i>0;)
            h += Hexadecimal::UpperByte[ n.get(--i) ];
        Algorithm::Skip(h,IsZero);
        h >> 'x' >> '0';
        std::cerr << std::setw(32) << H << " => " << h << std::endl;
        Y_ASSERT(h==H);
    }

    std::cerr << "-- testing mul/div" << std::endl;
    for(size_t k=0;k<1024;++k)
    {
        const apn lhs(ran,ran.in<size_t>(1,1000));
        const apn rhs(ran,ran.in<size_t>(1,1000));
        const apn prod = lhs * rhs;
        Y_ASSERT(prod/rhs==lhs);
        const apn m = lhs % rhs;
    }





}
Y_UDONE()

