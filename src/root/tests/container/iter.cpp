#include "y/container/iter/linear.hpp"
#include "y/container/iter/tests.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(container_iter)
{
    int arr[7] = { 1,2,3,4,5,6,7 };
    {
        Iter::Linear<Iter::Forward,int>       curr(arr);
        const Iter::Linear<Iter::Forward,int> last(arr+Y_Static_Size(arr));
        Iter::Test::Run(curr,last);
        
    }

}
Y_UDONE()

