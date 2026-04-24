
#include "y/calculus/prime/next.hpp"
#include "y/calculus/prime/prev.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/calculus/required-bits.hpp"

#include "y/utest/run.hpp"
using namespace Yttrium;

Y_UTEST(calculus_primes)
{
    Vector<uint64_t> p8;
    Vector<uint64_t> p16;


    uint64_t p = 0;
    size_t   n = 0;
    while(true)
    {
        p = Prime::Next(++p);
        ++n;
        const size_t pbits = RequiredBitsFor(p);
        std::cerr << std::setw(8) << p << " # " << std::setw(8) << n << " | bits=" << pbits << std::endl;

        if(pbits<=8) { p8 << p; continue; }
        if(pbits<=16) { Y_ASSERT(pbits>=9); p16 << p; continue; }

        break;
    }

    std::cerr << "p8=" << p8 << std::endl;
    std::cerr << "p16=" << p16 << std::endl;

    Y_PRINTV(p8.size());
    Y_PRINTV(p16.size());


}
Y_UDONE()

