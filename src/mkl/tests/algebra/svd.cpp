
#include "y/mkl/algebra/svd.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/container/cxx/array.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void testSVD(Core::Rand &ran)
    {
        std::cerr << "-- testing SVD" << std::endl;
        MKL::SVD<T> svd;
        Cameo::Addition<T> xadd;
        for(size_t n=1;n<=10;++n)
        {
            Matrix<T>  a(n,n);
            Matrix<T>   u(n,n), v(n,n);
            CxxArray<T> w(n);

            do {
                Random::Generate::Matrix(ran,a);
            } while( !svd.build(u,w,v,a) );



            Matrix<T> b(n,n);
            {
                Matrix<T> VT(TransposeOf,v);
                Matrix<T> dW(n,n); for(size_t i=1;i<=n;++i) dW[i][i] = w[i];
                Matrix<T> dWVT(n,n);
                dWVT.mmul(dW,VT);
                b.mmul(u,dWVT);
            }

            //std::cerr << "a=" << a << std::endl;
            //std::cerr << "u=" << u << std::endl;
            //std::cerr << "w=diagm(" << w << ")" << std::endl;
            //std::cerr << "v=" << v << std::endl;
            //std::cerr << "b=" << b << std::endl;

            xadd.ldz();
            for(size_t i=1;i<=n;++i)
            {
                for(size_t j=1;j<=n;++j)
                {
                    const T delta = b[i][j] - a[i][j];
                    xadd << delta*delta;
                }
            }
            const T r2 = xadd() / (T)(n*n);
            std::cerr << "\tr2=" << r2 << std::endl;
        }
        std::cerr << std::endl;
    }
}

Y_UTEST(algebra_svd)
{

    Core::Rand ran;

    testSVD<float>(ran);
    testSVD<double>(ran);
    testSVD<long double>(ran);
    testSVD<XReal<float>>(ran);
    testSVD<XReal<double>>(ran);
    testSVD<XReal<long double>>(ran);

}
Y_UDONE()

