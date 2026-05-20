#include "y/information/bwt/transformer.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/input.hpp"

using namespace Yttrium;

Y_UTEST(info_bwt)
{
    Information::BWT_Transformer bwt;

    if(argc>1)
    {
        String input;
        {
            InputFile fp(argv[1]);
            char c = 0;
            while(fp.query(c))
            {
                input << c;
            }
        }
        const size_t length = input.length();
        String       encoded(WithAtLeast,length,InitBlankString);
        const size_t pidx = bwt.encode( encoded(), input(), length );
        String       decoded(WithAtLeast,length,InitBlankString);
        bwt.decode(decoded(), encoded(), length,pidx);
        std::cerr << "input   = '" << input   << "'" << std::endl;
        std::cerr << "encoded = '" << encoded << "' [" << pidx << "]" << std::endl;
        std::cerr << "decoded = '" << decoded << "'" << std::endl;
        Y_CHECK(decoded==input);
    }


}
Y_UDONE()

