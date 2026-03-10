#include "y/utest/driver.hpp"
//#include "y/libc/sort.h"
//#include "y/core/display.hpp"
//#include "y/core/rand.hpp"
//#include "y/core/shuffle.hpp"
//#include "y/core/find.hpp"
//#include <ctime>

Y_UTEST_DECL(3)
{
    Y_UTEST(config_platform);

    Y_UTEST(core_display);
    Y_UTEST(core_rand);
}
Y_UTEST_EXEC()



#if 0
namespace
{
    static inline int compare(const void * const lhs, const void * const rhs, void * const) noexcept
    {
        return *(const int *)lhs - *(const int *)rhs;
    }

}

int main(int argc, char **argv)
{

    UTest::DriverWith<3> driver;
    {
        static const char * const name = "platform";
        extern int Y_UTest_platform(int,char **);
        driver(Y_UTest_platform,name);
    }
    driver.display();

    Core::Rand ran( (long)time(NULL) );
    for(size_t iter=0;iter<10;++iter)
    {
        std::cerr << ran() << " / " << ran.in<int>(-2,2) << std::endl;
    }

#if 0
    {
        static const char * const name = "platform";
        extern int Y_UTest_platform(int,char **);
        UTest t(name,Y_UTest_platform);
        if(0==t.proc) { std::cerr << "Bad Proc!" << std::endl; }
        t.proc(argc,argv);
    }
#endif

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

            Yttrium_Sort(arr,num,sizeof(arr[0]),compare,NULL,&tmp);
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
#endif

