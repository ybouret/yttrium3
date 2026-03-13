
#include "y/core/hindx.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/core/display.hpp"

#include "y/random/shuffle.hpp"
#include <ctime>

using namespace Yttrium;



Y_UTEST(core_hindx)
{
    Core::Rand   ran( (long) time(NULL) );
    int          arr[] = { 0, 1, 2, 3, 4, 5, 6 };
    const size_t num = sizeof(arr) / sizeof(arr[0]);
    size_t       idx[num];

    Random::Shuffle(ran,arr,num);
    Core::Display(std::cerr << "arr=",arr,num) << std::endl;

    Core::HIndx::Make(idx,arr,num,Sign::Increasing<int>);
    Core::Display(std::cerr << "idx=",idx,num) << std::endl;



}
Y_UDONE()
