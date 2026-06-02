
#include "y/mkl/algebra/cyclic.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"
#include <typeinfo>
#include "y/container/cxx/array.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testCyclic(Core::Rand & ran, const size_t nmax=10)
    {
        typedef typename MKL::ScalarFor<T>::Type SType;

        std::cerr << "-- " << typeid(T).name() << std::endl;
        Cameo::Addition<SType> sadd(nmax);
        const SType s0 = 0;
        for(size_t n=3;n<=nmax;++n)
        {
            std::cerr << "\tn=" << n << std::endl;
            MKL::Cyclic<T>  cy(n);
            CxxArray<T>     u(n), r(n), v(n);
            do
            {
                for(size_t i=1;i<=n;++i)
                {
                    while( MKL::Fabs<T>(cy.b[i]) <= s0)
                        cy.b[i] = Random::Gen<T>::Get(ran);
                }
                for(size_t i=2;i<=n;++i) cy.a[i] = Random::Gen<T>::Get(ran);
                for(size_t i=1;i<n;++i)  cy.c[i] = Random::Gen<T>::Get(ran);
                cy.alpha = Random::Gen<T>::Get(ran);
                cy.beta  = Random::Gen<T>::Get(ran);
                Random::Generate::Array(ran,r);
            } while( !cy.solve(u,r) );

            //std::cerr << cy << std::endl;

            cy.mul(v,u);
            //std::cerr << "r=" << r << std::endl;
            //std::cerr << "v=" << v << std::endl;
            SType den = 0;
            for (size_t i = n; i > 0; --i)
            {
                v[i] -= r[i]; 
                den += 1;
            }
            const SType r2 = sadd.mod2(v) / den;
            std::cerr << "\t\tr2=" << r2 << std::endl;
        }

    }
}

Y_UTEST(algebra_cyclic)
{
    Core::Rand ran;

    testCyclic<float>(ran);
    testCyclic< XReal<double> >(ran);
    testCyclic< Complex<long double>  >(ran);
    testCyclic< Complex< XReal<float> >  >(ran);
    testCyclic< apq >(ran);

}
Y_UDONE()
