#include "y/core/display.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(core_display)
{
    const int arr[] = { 1,2,3,4 };
    Core::Display(std::cerr,arr,sizeof(arr)/sizeof(arr[0])) << std::endl;
}
Y_UDONE()
