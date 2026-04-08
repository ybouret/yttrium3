#include "y/string/stride.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(string_stride)
{

    const char text[] = "Hello";
    std::cerr << text << " / " << StringLength(text) << std::endl;

    { Stride<char> s(10);   std::cerr << "stride=" << s << std::endl; }
    { Stride<char> s(text); std::cerr << "stride=" << s << std::endl;}

    {
        Stride<char> s(20);
        s.cat(text,StringLength(text)); std::cerr << s << std::endl;
        s.cat(",World",6);              std::cerr << s << std::endl;
        std::cerr << s.trim(4) << std::endl;
        std::cerr << s.skip(3) << std::endl;
    }



}
Y_UDONE()


