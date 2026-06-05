
#include "y/field/1d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(field_1d)
{
    Y_SIZEOF(Field::In1D<int>);
    Y_SIZEOF(Field::In1D<String>);

    {
        const Field::Layout1D L(1,10);
        Field::In1D<int>    F1i("F1i",L);
        Field::In1D<String> F1s("F1s",L);

    }

}
Y_UDONE()

