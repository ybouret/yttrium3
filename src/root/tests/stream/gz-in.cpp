#include "y/stream/gz/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_gz_in)
{
    if(argc>1)
    {
        GZ::Input fp(argv[1]);
        
    }
}
Y_UDONE()
