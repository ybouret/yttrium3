#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

#define GEN(TYPE) do { \
for(size_t iter=0;iter<4;++iter)\
std::cerr << std::setw(32) << #TYPE << " : " << std::setw(16) << Random::Gen<TYPE>::Get(ran) << std::endl; \
} while(false)

Y_UTEST(random_type_gen)
{
    Core::Rand ran;
    GEN(int);
    GEN(uint16_t);
    GEN(char);

    GEN(String);

    GEN(apn);
    GEN(apz);
    GEN(apq);

    GEN(float);
    GEN(double);
    GEN(long double);

    GEN(XReal<float>);
    GEN(XReal<double>);
    GEN(XReal<long double>);

    GEN(Complex<float>);
    GEN(Complex<double>);
    GEN(Complex<long double>);

    GEN(Complex<XReal<float>>);
    GEN(Complex<XReal<double>>);
    GEN(Complex<XReal<long double>>);

    GEN(V2D<float>);
    GEN(V2D<double>);
    GEN(V2D<long double>);

    GEN(V3D< XReal<float> >);
    GEN(V3D< XReal<double> >);
    GEN(V3D< XReal<long double> >);
}
Y_UDONE()

