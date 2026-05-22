#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

#define GEN(TYPE) do { \
for(size_t iter=0;iter<4;++iter)\
std::cerr << std::setw(16) << #TYPE << " : " << std::setw(16) << Random::Gen<TYPE>::Get(ran) << std::endl; \
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
}
Y_UDONE()

