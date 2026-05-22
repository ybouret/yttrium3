#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"
#include "y/container/cxx/array.hpp"
#include <typeinfo>

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testLU(Core::Rand &ran, const size_t nmax=8)
    {
        typedef typename MKL::ScalarFor<T>::Type SType;
        std::cerr << "-- LU<" << typeid(T).name() << ">" << std::endl;
        MKL::LU<T>             lu;
        Cameo::Addition<SType> sadd;

        for(size_t n=1;n<=nmax;++n)
        {
            Matrix<T> a0(n,n);
            Matrix<T> a(n,n);
            CxxArray<T> b(n),u(n),v(n);

            for(size_t iter=0;iter<4;++iter)
            {
                do
                {
                    Random::Generate::Matrix(ran,a0);
                    a.assign(a0);
                } while(!lu.build(a));

                std::cerr << "a  = " << a0 << std::endl;

                Random::Generate::Array(ran,b);
                //std::cerr << "b  = " << b << std::endl;
                lu.solve(a, u.ld(b) );
                //std::cerr << "u  = " << u << std::endl;

                a0.mul(v,u);
                //std::cerr << "v  = " << v << std::endl;
                a0.mulsub(v,u,b);
                //std::cerr << "d  = " << v << std::endl;
                const SType r2 = sadd.mod2(v) / (SType)n;
                std::cerr << " r2 = " << r2 << std::endl;
            }

        }

    }

}

Y_UTEST(algebra_lu)
{
    Core::Rand ran;
    testLU<float>(ran);
    testLU< Complex<double> >(ran);
    testLU< XReal<long double> >(ran);
    testLU< apq >(ran);
}
Y_UDONE()

