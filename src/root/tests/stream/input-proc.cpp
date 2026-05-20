#include "y/stream/proc/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_input_proc)
{
    if(argc>1)
    {
        InputProcess fp(argv[1]);
        String       line;
        while(fp.gets(line))
        {
            std::cerr << "-- " << line << std::endl;
        }

    }
}
Y_UDONE()
