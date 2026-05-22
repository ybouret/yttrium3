
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
    static inline void testAdj(Core::Rand &ran, const size_t nmax=5)
    {
        //typedef typename MKL::ScalarFor<T>::Type SType;
        std::cerr << "-- Adjoint<" << typeid(T).name() << ">" << std::endl;
        MKL::LU<T>             lu;
        for(size_t n=1;n<=nmax;++n)
        {
            Matrix<T> a(n,n);
            Matrix<T> b(n,n);
            Matrix<T> p(n,n);
            T         d (0);
            {
                Matrix<T> tmp(n,n);
                do
                {
                    Random::Generate::Matrix(ran,a);
                    tmp.assign(a);
                } while(!lu.build(tmp));
                d = lu.det(tmp);
            }

            lu.adjoint(b,a);
            p.mmul(a,b);
            for(size_t i=n;i>0;--i) p[i][i] /= d;
            //std::cerr << "a=" << a << std::endl;
            //std::cerr << "b=" << b << std::endl;
            std::cerr << "p=" << p << std::endl;
            //std::cerr << "d=" << d << std::endl;
        }

    }

}

Y_UTEST(algebra_adjoint)
{
    Core::Rand ran;
    testAdj<float>(ran);
    testAdj< Complex<double> >(ran);
    testAdj< XReal<long double> >(ran);
    testAdj< apq >(ran);
}
Y_UDONE()

