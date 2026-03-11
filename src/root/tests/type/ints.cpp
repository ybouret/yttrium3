
#include "y/type/ints.hpp"
#include "y/utest/run.hpp"
#include <cassert>
#include <typeinfo>

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void showInt(const char * const name)
    {
        assert(name);
        std::cerr << "<" << name << "> = " << typeid(T).name() << std::endl;
        Y_PRINTV( IntegerFor<T>::Bytes );
        std::cerr << "==> " << typeid( typename IntegerFor<T>::Type ).name() << std::endl;
        Y_PRINTV( IntegerFor<T>::Minimum );
        Y_PRINTV( IntegerFor<T>::Maximum );
        std::cerr << std::endl;
    }

}

#define ShowInt(TYPE) showInt<TYPE>( #TYPE )

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

    std::cerr << std::endl << "Matching:" << std::endl;
    ShowInt(int);
    ShowInt(size_t);
    ShowInt(unit_t);

    
}
Y_UDONE()

