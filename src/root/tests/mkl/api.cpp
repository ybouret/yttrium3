
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"

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
}

Y_UTEST(mkl_api)
{
    showScalarFor<int>();
    showScalarFor<float>();
    showScalarFor< Complex<float> >();
    showScalarFor< XReal<double> >();

}
Y_UDONE()

