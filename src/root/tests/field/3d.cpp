


#include "y/field/3d.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testField(Field::In3D<T> &F, Core::Rand &ran)
    {
        std::cerr << "-- testing " << F.name << std::endl;

        for(unit_t z=F->lower.z;z<=F->upper.z;++z)
            for(unit_t y=F->lower.y;y<=F->upper.y;++y)
                for(unit_t x=F->lower.x;x<=F->upper.x;++x)
                {
                    F[z][y][x] = Random::Gen<T>::Get(ran);
                }

        const Field::In3D<T> &C = F;
        for(unit_t z=F->lower.z;z<=F->upper.z;++z)
            for(unit_t y=F->lower.y;y<=F->upper.y;++y)
            {
                const Field::In1D<T> &Czy = C[z][y];
                std::cerr << Czy.name << ":";
                for(unit_t x=F->lower.x;x<=F->upper.x;++x)
                {
                    std::cerr << ' ' << Czy[x];
                }
                std::cerr << std::endl;
            }
    }

}

Y_UTEST(field_3d)
{

    Core::Rand ran;
    const Field::Layout3D L( Field::Coord3D(-1,-2,-3), Field::Coord3D(4,5,6) );
    Field::In3D<int>      F3i("F3i",L); testField(F3i,ran);
    Field::In3D<String>   F3s("F3s",L); testField(F3s,ran);

}
Y_UDONE()

