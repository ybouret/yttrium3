#include "y/mkl/numeric.hpp"
#include "y/utest/run.hpp"
#include <typeinfo>

using namespace Yttrium;
using namespace MKL;


#define SHOW(VAR) std::cerr << std::setw(16) << #VAR << " = " << std::setw(16) << Numeric<T>::VAR << std::endl;

template <typename T> static inline void showNumeric()
{
    std::cerr << "-- Numeric<" << typeid(T).name() << ">" << std::endl;
    SHOW(RADIX);
    SHOW(PI);
    SHOW(EPSILON);
    SHOW(MAX);
    SHOW(MIN);
    SHOW(MANT_DIG);
    SHOW(DIG);
    SHOW(MIN_EXP);
    SHOW(MAX_EXP);
    SHOW(MAX_10_EXP);
    SHOW(MIN_10_EXP);
    SHOW(FTOL);
    SHOW(SQRT_EPSILON);
    SHOW(GOLDEN);
    SHOW(INV_GOLDEN);
    SHOW(THETA);
}

Y_UTEST(mkl_numeric)
{
    showNumeric<float>();
    showNumeric<double>();
    showNumeric<long double>();

}
Y_UDONE()

