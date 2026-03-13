
#include "y/calculus/meta2.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_meta2)
{

    Y_PRINTV(MetaPrevPowerOfTwo<1>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<2>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<3>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<4>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<5>::Value);
    Y_PRINTV(MetaPrevPowerOfTwo<40>::Value);
    std::cerr << std::endl;

    Y_PRINTV(MetaNextPowerOfTwo<0>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<1>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<2>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<3>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<4>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<5>::Value);
    Y_PRINTV(MetaNextPowerOfTwo<40>::Value);

}
Y_UDONE()

