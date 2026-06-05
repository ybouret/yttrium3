



#include "y/field/4d.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testField(Field::In4D<T> &F, Core::Rand &ran)
    {
        std::cerr << "-- testing " << F.name << std::endl;

        for(unit_t w=F->lower.w;w<=F->upper.w;++w)
            for(unit_t z=F->lower.z;z<=F->upper.z;++z)
                for(unit_t y=F->lower.y;y<=F->upper.y;++y)
                    for(unit_t x=F->lower.x;x<=F->upper.x;++x)
                    {
                        F[w][z][y][x] = Random::Gen<T>::Get(ran);
                    }

        const Field::In4D<T> &C = F;
        for(unit_t w=F->lower.w;w<=F->upper.w;++w)
            for(unit_t z=F->lower.z;z<=F->upper.z;++z)
                for(unit_t y=F->lower.y;y<=F->upper.y;++y)
                {
                    const Field::In1D<T> &Cwzy = C[w][z][y];
                    std::cerr << Cwzy.name << ":";
                    for(unit_t x=F->lower.x;x<=F->upper.x;++x)
                    {
                        std::cerr << ' ' << Cwzy[x];
                    }
                    std::cerr << std::endl;
                }

    }

}

Y_UTEST(field_4d)
{

    Core::Rand ran;
    const Field::Layout4D L( Field::Coord4D(-1,-2,-3,-4), Field::Coord4D(5,6,7,8) );
    Field::In4D<int>      F4i("F4i",L); testField(F4i,ran);
    Field::In4D<String>   F4s("F4s",L); testField(F4s,ran);

}
Y_UDONE()

