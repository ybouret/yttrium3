
#include "y/core/rand.hpp"
#include "y/utest/run.hpp"
#include <ctime>

using namespace Yttrium;

Y_UTEST(core_rand)
{
    Core::Rand ran;

    for(size_t i=0;i<20;++i)
    {
        std::cerr << std::setw(10) << ran() << " | " << std::setw(4) << ran.in<int>(-5,5) << std::endl;
    }

    double sum = 0;
    size_t count = 0;
    for(size_t i=0;i<100000;++i)
    {
        ++count;
        sum +=  ran.toss<unsigned>(10);
    }
    const double ave = sum / count;
    std::cerr << "ave=" << ave << std::endl;

}
Y_UDONE()
