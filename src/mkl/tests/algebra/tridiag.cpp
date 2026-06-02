
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
    void testTridiag(Core::Rand & ran, const size_t nmax=10)
    {
        typedef typename MKL::ScalarFor<T>::Type SType;
        
        std::cerr << "-- " << typeid(T).name() << std::endl;
        Cameo::Addition<SType> sadd(nmax);
        for(size_t n=1;n<=nmax;++n)
        {
            std::cerr << "\tn=" << n << std::endl;
            MKL::TriDiag<T> td(n);
            CxxArray<T>     u(n), r(n), v(n);
            do
            {
                for(size_t i=1;i<=n;++i) td.b[i] = Random::Gen<T>::Get(ran);
                for(size_t i=2;i<=n;++i) td.a[i] = Random::Gen<T>::Get(ran);
                for(size_t i=1;i<n;++i)  td.c[i] = Random::Gen<T>::Get(ran);
                Random::Generate::Array(ran,r);
            } while( !td.solve(u,r) );

            //std::cerr << td << std::endl;

            td.mul(v,u);
            //std::cerr << "r=" << r << std::endl;
            //std::cerr << "v=" << v << std::endl;
            SType den = 0;
            for (size_t i = n; i > 0; --i) {
                v[i] -= r[i];
                den += 1;
            }
            const SType r2 = sadd.mod2(v) / den;
            std::cerr << "\t\tr2=" << r2 << std::endl;
        }

    }
}

Y_UTEST(algebra_tridiag)
{
    Core::Rand ran;

    testTridiag<float>(ran);
    testTridiag< XReal<double> >(ran);
    testTridiag< Complex<long double>  >(ran);
    testTridiag< Complex< XReal<float> >  >(ran);
    testTridiag< apq >(ran);

}
Y_UDONE()

