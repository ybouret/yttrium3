
#include "y/type/ints.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(type_ints)
{
    std::cerr << "Unsigned" << std::endl;
    Y_PRINTV( (int) UnsignedInt<uint8_t>::Maximum );
    Y_PRINTV( (int) UnsignedInt<uint8_t>::Minimum );

    Y_PRINTV(       UnsignedInt<uint16_t>::Maximum );
    Y_PRINTV(       UnsignedInt<uint16_t>::Minimum );

    Y_PRINTV(       UnsignedInt<uint32_t>::Maximum );
    Y_PRINTV(       UnsignedInt<uint32_t>::Minimum );

    Y_PRINTV(       UnsignedInt<uint64_t>::Maximum );
    Y_PRINTV(       UnsignedInt<uint64_t>::Minimum );

    std::cerr << std::endl << "Signed:" << std::endl;

    Y_PRINTV( (int) SignedInt<int8_t>::Maximum );
    Y_PRINTV( (int) SignedInt<int8_t>::Minimum );

    Y_PRINTV(       SignedInt<int16_t>::Maximum );
    Y_PRINTV(       SignedInt<int16_t>::Minimum );

    Y_PRINTV(       SignedInt<int32_t>::Maximum );
    Y_PRINTV(       SignedInt<int32_t>::Minimum );

    Y_PRINTV(       SignedInt<int64_t>::Maximum );
    Y_PRINTV(       SignedInt<int64_t>::Minimum );

}
Y_UDONE()

