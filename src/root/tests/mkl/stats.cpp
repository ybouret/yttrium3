
#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/sequence/list.hpp"
#include "y/core/rand.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;
using namespace MKL;



Y_UTEST(mkl_stats)
{
    Core::Rand    ran;
    Vector<float> vec;
    List<float>   lst;

    for(size_t i=ran.leq<size_t>(100);i>0;--i)
    {
        const float f = ran();
        vec << f;
        lst << f;
    }
    const size_t           size = vec.size();
    Cameo::Addition<float> xadd;
    Random::Shuffle(ran, vec(), size );
    const float ave1 = Statistics::Average::Of(vec,xadd); std::cerr << "ave1 = " << ave1 << std::endl;
    Random::Shuffle(ran, vec(), size );
    const float ave2 = Statistics::Average::Of(vec(),size,xadd); std::cerr << "ave2 = " << ave2 << std::endl;
    const float ave3 = Statistics::Average::Of(lst,xadd); std::cerr << "ave3 = " << ave3 << std::endl;



}
Y_UDONE()

