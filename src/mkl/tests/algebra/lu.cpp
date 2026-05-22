#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testLU(Core::Rand &ran, const size_t nmax=3)
    {
        MKL::LU<T> lu;
        for(size_t n=1;n<=nmax;++n)
        {
            Matrix<T> a0(n,n);
            Matrix<T> a(n,n);

            do
            {
                Random::Generate::Matrix(ran,a0);
                a.assign(a0);
            } while(!lu.build(a));

            std::cerr << "a=" << a0 << std::endl;

        }

    }

}

Y_UTEST(algebra_lu)
{
    Core::Rand ran;

    testLU<float>(ran);
}
Y_UDONE()

