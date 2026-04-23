

#include "y/container/sequence/list.hpp"
#include "y/core/rand.hpp"
#include "y/utest/run.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(container_list)
{
    Core::Rand ran;
    //const int arr[7] = { 1,2,3,4,5,6,7 };

    {
        List<double> L;
        for(size_t i=10;i>0;--i)
        {
            const double d = ran();
            if(ran.heads()) L << d; else L >> d;
            std::cerr << L << std::endl;
        }

        Iter::Test::All(L);
        


    }

#if 0
    {
        Vector<float> v(Replicate,arr,Y_Static_Size(arr));
        std::cerr << v << std::endl;
        Vector<double> d(CopyOf,v);
    }
#endif


}
Y_UDONE()

