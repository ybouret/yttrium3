#include "y/calculus/gcd.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_gcd)
{
    for(int i=1;i<argc;++i)
    {
        const long a = atol(argv[i]);
        for(int j=i;j<argc;++j)
        {
            const long b = atol(argv[j]);
            std::cerr << "gcd(" << a << "," << b << ")=" << GreatestCommonDivisor(a,b) << std::endl;
        }
    }


}
Y_UDONE()

