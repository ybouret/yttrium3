
#include "y/mkl/api/fpow.hpp"
#include "y/mkl/api/sgn.hpp"
#include "y/mkl/api/pythagoras.hpp"

#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/apex/integer.hpp"

#include "y/utest/run.hpp"
#include <typeinfo>

using namespace Yttrium;
using namespace MKL;

namespace {
    template <typename T>
    void showScalarFor()
    {
        typedef typename ScalarFor<T>::Type ScalarType;
        std::cerr << "ScalarFor " << typeid(T).name() << " => " << typeid(ScalarType).name() << std::endl;
    }

    template <typename T> static inline
    void showPythagoras(const T a, const T b, const T c)
    {
        std::cerr << "-- <" << typeid(T).name() << ">" << std::endl;
        std::cerr << "\t(|" << a << "|^2+|" << b << "|^2)^(1/2)=" << Pythagoras<T>(a,b) << std::endl;
        std::cerr << "\t(|" << b << "|^2+|" << c << "|^2)^(1/2)=" << Pythagoras<T>(b,c) << std::endl;
        std::cerr << "\t(|" << a << "|^2+|" << b << "|^2+|" << c << "|^2)^(1/2)=" << Pythagoras<T>(a,b,c) << std::endl;
    }

    template <typename T> static inline
    void showFpow(const T x, const T a)
    {
        std::cerr << "-- " << x << "^" << a << " = " << Fpow(x,a) << std::endl;
    }

}

Y_UTEST(mkl_api)
{
    showScalarFor<int>();
    showScalarFor<float>();
    showScalarFor< Complex<float> >();
    showScalarFor< XReal<double> >();

    showPythagoras<float>(2,3,4);
    showPythagoras< XReal<long double> >(2,3,4);

    showFpow<float>(10,2.2);
    showFpow< XReal<double> >(10,2.2);

}
Y_UDONE()

