
#include "y/mkl/algebra/tridiag.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"
#include <typeinfo>
#include "y/container/cxx/array.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testTridiag(Core::Rand & ran, const size_t nmax=5)
    {
        std::cerr << "-- " << typeid(T).name() << std::endl;
        for(size_t n=1;n<=nmax;++n)
        {
            MKL::TriDiag<T> td(n);
            CxxArray<T>     u(n), r(n);
            do
            {
                for(size_t i=1;i<=n;++i) td.b[i] = Random::Gen<T>::Get(ran);
                for(size_t i=2;i<=n;++i) td.a[i] = Random::Gen<T>::Get(ran);
                for(size_t i=1;i<n;++i)  td.c[i] = Random::Gen<T>::Get(ran);
                Random::Generate::Array(ran,r);
            } while( !td.solve(u,r) );



            std::cerr << td << std::endl;
        }

    }
}

Y_UTEST(algebra_tridiag)
{
    Core::Rand ran;

    testTridiag<float>(ran);

}
Y_UDONE()

