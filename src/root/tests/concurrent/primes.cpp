#include "y/calculus/prime/test.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class PrimeDetector
    {
    public:

        inline virtual ~PrimeDetector() noexcept {}
        
    private:
        Y_Disable_Copy_And_Assign(PrimeDetector);
    };
}

Y_UTEST(concurrent_primes)
{

}
Y_UDONE()

