

#include "y/cameo/multiplication.hpp"
#include "y/utest/run.hpp"

#include "y/apex/rational.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testMult()
    {
        Cameo::Multiplication<T> cm; std::cerr << cm.callSign() << std::endl;
        cm << 1000 << 20 << 300 << 4;
        std::cerr << cm << std::endl;
        {
            const Cameo::Multiplication<T> tmp(cm);
            std::cerr << tmp << std::endl;
        }
        std::cerr << cm() << std::endl;
    }
}

Y_UTEST(cameo_multiplication)
{

    testMult<apq>();
    testMult<apn>();
    testMult<apz>();
    testMult<int>();
    testMult<uint32_t>();
    testMult<double>();
    testMult< XReal<double> >();
    testMult< Complex<float> >();
    
}
Y_UDONE()


