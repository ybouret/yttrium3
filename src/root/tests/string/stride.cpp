#include "y/string/stride.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(string_stride)
{

    const char text[] = "Hello";
    std::cerr << text << " / " << StringLength(text) << std::endl;

    { Core::Stride<char> s(10);   std::cerr << "stride=" << s << std::endl; }
    { Core::Stride<char> s(text); std::cerr << "stride=" << s << std::endl;}

    {
        Core::Stride<char> s(20);
        s.cat(text,StringLength(text)); std::cerr << s << std::endl;
        s.cat(",World",6);              std::cerr << s << std::endl;
        s.trim(4); std::cerr << s << std::endl;
        s.skip(3); std::cerr << s << std::endl;
    }

    Y_SIZEOF(Core::Stride<char>);
    Y_SIZEOF(Core::Stride<uint32_t>);



}
Y_UDONE()


