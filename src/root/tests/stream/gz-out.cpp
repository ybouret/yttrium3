#include "y/stream/gz/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_gz_out)
{
    Core::Rand ran;

    if(argc>1)
    {
        InputFile  input(argv[1]);
        const int  level = argc > 2 ? ASCII::Convert::To<int>(argv[2],"level",0) : 7;
        GZ::Output output("output.gz",level);

        while(true)
        {
            if( ran.heads() )
            {
                char c = 0;
                if(input.query(c))
                {
                    output.write(c);
                }
                else
                    break;
            }
            else
            {
                char buffer[32];
                const size_t nr = input.query(buffer,sizeof(buffer));
                if(nr)
                {
                    output.write(buffer,nr);
                }
                else
                {
                    break;
                }
            }
        }

    }
}
Y_UDONE()


