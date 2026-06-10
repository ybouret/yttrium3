
#include "y/mkl/statistics/average.hpp"
#include "y/mkl/statistics/variance.hpp"
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

    for(size_t i=1000+ran.leq<size_t>(10000);i>0;--i)
    {
        const float f = ran();
        vec << f;
        lst << f;
    }
    const size_t           size = vec.size();
    Cameo::Addition<float> xadd;
    Random::Shuffle(ran, vec(), size );
    const float aveA = Statistics::Average::Of(vec,xadd);        std::cerr << "aveA = " << aveA << std::endl;
    const float varA = Statistics::Variance::Of(vec,aveA,xadd);  std::cerr << "varA = " << varA << std::endl;

    Random::Shuffle(ran, vec(), size );
    const float aveB = Statistics::Average::Of(vec(),size,xadd);        std::cerr << "aveB = " << aveB << std::endl;
    const float varB = Statistics::Variance::Of(vec(),size,aveB,xadd);  std::cerr << "varB = " << varB << std::endl;

    const float aveC = Statistics::Average::Of(lst,xadd);        std::cerr << "aveC = " << aveC << std::endl;
    const float varC = Statistics::Variance::Of(lst,aveC,xadd);  std::cerr << "varC = " << varC << std::endl;



}
Y_UDONE()

