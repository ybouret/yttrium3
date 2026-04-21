#include "y/container/cxx/array.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(container_cxx_array)
{
#if 1

    { CxxArray<int>   iarr(0); std::cerr << iarr << std::endl; }
    { CxxArray<float> farr(6); std::cerr << farr << ", capa=" << farr.capacity() << std::endl; }
    { CxxArray<int>   iarr(3,1); std::cerr << iarr << std::endl; }
    { const int i = 2; CxxArray<apq> qarr(5,CopyOf,i); std::cerr << qarr << std::endl; }

    {
        CxxArray<apn> arr(7);
        for(size_t i=arr.size();i>0;--i) arr[i] = i;
        Iter::Test::All(arr);
    }
#endif
    
}
Y_UDONE()

