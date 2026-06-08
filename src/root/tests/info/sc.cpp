
#include "y/information/stream/move-to-front.hpp"
#include "y/information/stream/delta.hpp"
#include "y/information/stream/arc4.hpp"
#include "y/information/stream/verbatim.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/input.hpp"

#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(info_sc)
{

    Information::MoveToFront::Encoder mtfEnc;
    Information::MoveToFront::Decoder mtfDec;

    Information::Delta::Encoder deltafEnc;
    Information::Delta::Decoder deltafDec;

    Information::Verbatim::Encoder verbatimfEnc;
    Information::Verbatim::Decoder verbatimfDec;

    const char * const key = "hello";
    Information::ARC4::Encoder arc4Enc(key);
    Information::ARC4::Decoder arc4Dec(key);
    


}
Y_UDONE()

