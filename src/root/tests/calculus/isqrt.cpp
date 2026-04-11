#include "y/calculus/isqrt.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    template <typename T>
    static inline void TestISQRT()
    {
        for(T x=0; x <= 255;++x)
        {
            const T s = IntegerSquareRoot(x);
            std::cerr << std::setw(3) << x << " => " << std::setw(3) << s << std::endl;
            Y_ASSERT(s*s<=x);
        }
    }
}

Y_UTEST(calculus_isqrt)
{
    TestISQRT<int>();
    TestISQRT<unsigned>();

    Y_PRINTV(Calculus::IntegerSquareRoot::TableLast);
    Y_PRINTV(Calculus::IntegerSquareRoot::TableSize);

}
Y_UDONE()


