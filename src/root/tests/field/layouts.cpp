#include "y/field/layout.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/v4d.hpp"

using namespace Yttrium;


Y_UTEST(field_layouts)
{
    {
        Field::Layout<unit_t> L(1,5);
        std::cerr << L << std::endl;
    }

    {
        Field::Layout< V2D<unit_t> > L( V2D<unit_t>(-1,-2), V2D<unit_t>(3,4) );
        std::cerr << L << std::endl;
    }

}
Y_UDONE()

