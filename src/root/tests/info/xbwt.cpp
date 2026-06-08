
#include "y/information/bwt/transformer.hpp"
#include "y/information/stream/move-to-front.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/input.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(info_xbwt)
{
    Information::BWT_Transformer         bwt;
    Information::MoveToFront::Encoder    mtf;
    Information::MoveToFront::Decoder    dec;

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
        mtf.restart();
        dec.restart();
        const size_t length = input.length();
        String       encoded(WithAtLeast,length,InitBlankString);
        const size_t pidx = bwt.encode( encoded(), input(), length );
        std::cerr << "input   = '" << input   << "'" << std::endl;
        std::cerr << "encoded = '" << encoded << "' [" << pidx << "]" << std::endl;
        Hexadecimal::Display(std::cerr << "raw=",encoded.c_str(),length) << std::endl;
        mtf.transform(encoded(), encoded(), length);
        Hexadecimal::Display(std::cerr << "mtf=",encoded.c_str(),length) << std::endl;
        dec.transform(encoded(), encoded(), length);
        Hexadecimal::Display(std::cerr << "dec=",encoded.c_str(),length) << std::endl;


#if 0
        String       decoded(WithAtLeast,length,InitBlankString);
        bwt.decode(decoded(), encoded(), length,pidx);
        std::cerr << "input   = '" << input   << "'" << std::endl;
        std::cerr << "encoded = '" << encoded << "' [" << pidx << "]" << std::endl;
        std::cerr << "decoded = '" << decoded << "'" << std::endl;
        Y_CHECK(decoded==input);
#endif
    }


}
Y_UDONE()

