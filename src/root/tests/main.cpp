#include "y/utest/driver.hpp"
#include "y/libc/sort.h"
#include "y/core/display.hpp"
#include "y/core/rand.hpp"
#include "y/core/shuffle.hpp"
#include "y/core/find.hpp"

#include <ctime>

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

    Core::Rand ran( (long)time(NULL) );
    for(size_t iter=0;iter<10;++iter)
    {
        std::cerr << ran() << " / " << ran.in<int>(-2,2) << std::endl;
    }

    //extern UTest::Proc Y_UTest_platform;
    //UTest t("platform",Y_UTest_platform);
    //t.proc(argc,argv);

    {
        size_t       arr[] = {0,1,2,3,4, 5, 6};
        const size_t num   = sizeof(arr)/sizeof(arr[0]);
        size_t       tmp   = 0;

        for(size_t iter=0;iter<10;++iter)
        {
            Core::Shuffle(ran,arr,num);
            Core::Display(std::cerr,arr,num) << " -> ";
            for(size_t i=0;i<num;++i)
            {
                if(!Core::Find(i,arr,num))
                {
                    std::cerr << "missing " << i << std::endl;
                    return 1;
                }
            }

            Yttrium_Sort(arr,num,sizeof(arr[0]),compare,&tmp);
            Core::Display(std::cerr,arr,num) << std::endl;
            for(size_t i=0;i<num;++i)
            {
                if(i!=arr[i])
                {
                    std::cerr << "invalid " << i << std::endl;
                }
            }
        }

 

    }

    return 0;
}
