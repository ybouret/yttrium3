#include "y/core/hsort.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/core/display.hpp"

#include "y/random/shuffle.hpp"
#include "y/core/test-ordered.hpp"
#include <ctime>

using namespace Yttrium;



Y_UTEST(core_hsort)
{
    Core::Rand   ran( (long) time(NULL) );
    int          arr[] = { 0, 1, 2, 3, 4, 5, 6 };
    const size_t num = sizeof(arr) / sizeof(arr[0]);

    Random::Shuffle(ran,arr,num);
    Core::Display(std::cerr,arr,num) << std::endl;
    Core::HSort::Make(arr,num,Sign::Increasing<int>);

    Y_CHECK(Core::TestOrdered::Array(arr,num,Sign::Increasing<int>, Sign::LooselyIncreasing));
    Y_CHECK(Core::TestOrdered::Array(arr,num,Sign::Increasing<int>, Sign::StriclyIncreasing));



    Core::Display(std::cerr,arr,num) << std::endl;
    Core::HSort::Decreasing(arr,num);

    Y_CHECK(Core::TestOrdered::Array(arr,num,Sign::Decreasing<int>, Sign::LooselyIncreasing));
    Y_CHECK(Core::TestOrdered::Array(arr,num,Sign::Decreasing<int>, Sign::StriclyIncreasing));
    Core::Display(std::cerr,arr,num) << std::endl;

}
Y_UDONE()
