#include "y/rtld/dll.hpp"
#include "y/utest/run.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

Y_UTEST(rtld)
{

    if(argc>1)
    {
        DLL dll(argv[1]);
        uint32_t * const data = dll.queryData<uint32_t>("Data");
        if(data)
        {
            Core::Display(std::cerr << "Data=",data,4) << std::endl;
        }

        typedef double (*Proc)(double);
        Proc sine = dll.queryProc<Proc>("Sine");
        if(sine)
        {
            for(double x=0;x<=1;x+=0.1)
            {
                std::cerr << x << " -> " << sine(x) << std::endl;
            }
        }
    }

}
Y_UDONE()

