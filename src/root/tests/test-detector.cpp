
#include "y/utest/run.hpp"
#include <type_traits>

// https://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class

namespace Yttrium
{

    template <typename T, typename = int>
    struct HasX : std::false_type { };

    template <typename T>
    struct HasX <T, decltype((void) T::x, 0)> : std::true_type { };
}

namespace
{
    struct A { int x; };
    struct B { int y; };
}

using namespace Yttrium;

Y_UTEST(detector)
{
    Y_PRINTV( HasX<A>::value );
    Y_PRINTV( HasX<B>::value );
}
Y_UDONE()
