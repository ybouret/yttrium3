#include "y/container/cxx/array.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(container_cxx_array)
{

    { CxxArray<int>   iarr(0); std::cerr << iarr << std::endl; }
    { CxxArray<float> farr(7); std::cerr << farr << ", capa=" << farr.capacity() << std::endl; }
    { CxxArray<int>   iarr(3,1); std::cerr << iarr << std::endl; }
    { const int i = 2; CxxArray<apq> qarr(5,CopyOf,i); std::cerr << qarr << std::endl; }

}
Y_UDONE()

