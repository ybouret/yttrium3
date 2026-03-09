#include "y/utest/driver.hpp"
#include "y/libc/sort.h"
#include "y/core/display.hpp"

using namespace Yttrium;

namespace
{
    static inline int compare(const void * const lhs, const void * const rhs) noexcept
    {
        return *(const int *)lhs - *(const int *)rhs;
    }
}
int main(int argc, char **argv)
{

    //extern UTest::Proc Y_UTest_platform;
    //UTest t("platform",Y_UTest_platform);
    //t.proc(argc,argv);

    {
        int arr[5] = {5,4,3,2,1};
        int tmp    = 0;
        Core::Display(std::cerr,arr,sizeof(arr)/sizeof(arr[0])) << std::endl;
        Yttrium_Sort(arr,sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), compare, &tmp);
        Core::Display(std::cerr,arr,sizeof(arr)/sizeof(arr[0])) << std::endl;

    }

    return 0;
}
