
#include "y/field/1d.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testField(Field::In1D<T> &F, Core::Rand &ran)
    {
        std::cerr << "-- testing " << F.name << std::endl;
        for(unit_t x=F->lower;x<=F->upper;++x)
        {
            F[x] = Random::Gen<T>::Get(ran);
            std::cerr << F.name << "[" << x << "]=" << F[x] << std::endl;
        }

    }
}


Y_UTEST(field_1d)
{
    Y_SIZEOF(Field::In1D<int>);
    Y_SIZEOF(Field::In1D<String>);

    Core::Rand ran;
    {
        const Field::Layout1D L(-5,6);
        {Field::In1D<int>    F1i("F1i",L); testField(F1i,ran);}
        {Field::In1D<String> F1s("F1s",L); testField(F1s,ran);}


        char data[128];
        { Field::In1D<int>    F1c("F1c",L,data); testField(F1c,ran); }

    }

}
Y_UDONE()

