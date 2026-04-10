#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"

#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(apex_n)
{
    const uint64_t n = 0x12345;
    apn            N = n;
    std::cerr << Hexadecimal(n) << " => " << N << std::endl;
}
Y_UDONE()

