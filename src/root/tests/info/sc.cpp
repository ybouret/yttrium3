
#include "y/information/stream/move-to-front.hpp"
#include "y/information/stream/delta.hpp"
#include "y/information/stream/arc4.hpp"
#include "y/information/stream/verbatim.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/input.hpp"

#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

namespace
{
    static inline
    void testSC(Information::StreamCipher &encoder,
                Information::StreamCipher &decoder,
                const String              &org)
    {
        const size_t n = org.size();
        String enc(WithAtLeast,n,InitBlankString);
        String dec(WithAtLeast,n,InitBlankString);

        encoder.transform( (void*)enc.c_str(), org.c_str(), n);
        decoder.transform( (void*)dec.c_str(), enc.c_str(), n);

        std::cerr << std::setw(16) << encoder.callSign() << " : ";
        std::cerr << org << " => ";
        Hexadecimal::Display(std::cerr,enc.c_str(),n);
        std::cerr << " => " << dec << std::endl;



    }
}

Y_UTEST(info_sc)
{

    Information::MoveToFront::Encoder mtfEnc;
    Information::MoveToFront::Decoder mtfDec;

    Information::Delta::Encoder deltaEnc;
    Information::Delta::Decoder deltaDec;

    Information::Verbatim::Encoder verbatimfEnc;
    Information::Verbatim::Decoder verbatimfDec;

    const char * const key = "hello";
    Information::ARC4::Encoder arc4Enc(key);
    Information::ARC4::Decoder arc4Dec(key);

    if(argc>1)
    {
        InputFile fp(argv[1]);
        String    line;
        while(fp.gets(line))
        {
            testSC(mtfEnc,mtfDec,line);
            testSC(deltaEnc,deltaDec,line);
            testSC(arc4Enc,arc4Dec,line);
        }
    }


}
Y_UDONE()

