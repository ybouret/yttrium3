

#include "y/field/2d.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testField(Field::In2D<T> &F, Core::Rand &ran)
    {
        std::cerr << "-- testing " << F.name << std::endl;

        for(unit_t y=F->lower.y;y<=F->upper.y;++y)
            for(unit_t x=F->lower.x;x<=F->upper.x;++x)
            {
                F[y][x] = Random::Gen<T>::Get(ran);
            }

        const Field::In2D<T> &C =F;
        for(unit_t y=F->lower.y;y<=F->upper.y;++y)
        {
            const Field::In1D<T> &Cy = C[y];
            std::cerr << Cy.name << ":";
            for(unit_t x=F->lower.x;x<=F->upper.x;++x)
            {
                std::cerr << ' ' << Cy[x];
            }
            std::cerr << std::endl;
        }


    }
}

Y_UTEST(field_2d)
{
    Y_SIZEOF(Field::In2D<int>);
    Y_SIZEOF(Field::In2D<String>);

    Core::Rand ran;
    const Field::Layout2D L( Field::Coord2D(-1,-2), Field::Coord2D(3,4) );
    Field::In2D<int>      F2i("F2i",L); testField(F2i,ran);
    Field::In2D<String>   F2s("F2s",L); testField(F2s,ran);

}
Y_UDONE()

