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
    int          arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    const size_t num = Y_Static_Size(arr);

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

    Random::Shuffle(ran,arr,num);
    char chr[num]; for(size_t i=0;i<num;++i) chr[i] = 'A' + (char)i;
    Core::Display(std::cerr,arr,num) << " => ";
    Core::Display(std::cerr,chr,num) << std::endl;

    Core::HSort::Make(arr,num,Sign::Increasing<int>,chr);
    Core::Display(std::cerr,arr,num) << " => ";
    Core::Display(std::cerr,chr,num) << std::endl;

}
Y_UDONE()
