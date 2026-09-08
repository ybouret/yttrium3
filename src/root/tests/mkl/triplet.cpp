#include "y/mkl/triplet.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(mkl_triplet)
{
    MKL::Triplet<double> t = { 1, 0, 0.1 };
    Y_PRINTV(t);
    Y_PRINTV(t.middle());
}
Y_UDONE()
