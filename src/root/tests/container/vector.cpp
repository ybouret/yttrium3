
#include "y/container/sequence/vector.hpp"
#include "y/core/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(container_vector)
{
    Core::Rand ran;
    const int arr[7] = { 1,2,3,4,5,6,7 };

    {
        Vector<double> v;
        for(size_t i=10;i>0;--i)
        {
            const double d = ran();
            if(ran.heads()) v << d; else v >> d;
            std::cerr << v << std::endl;
        }
    }

    {
        Vector<float> v(Replicate,arr,Y_Static_Size(arr));
        std::cerr << v << std::endl;
        Vector<double> d(CopyOf,v);
    }



}
Y_UDONE()

