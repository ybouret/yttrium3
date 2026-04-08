#include "y/string/stride.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(string_stride)
{

    const char text[] = "Hello";
    std::cerr << text << " / " << StringLength(text) << std::endl;
    { Stride<char> s(10);   std::cerr << "stride=" << s << std::endl; }
    { Stride<char> s(text); std::cerr << "stride=" << s << std::endl;}


}
Y_UDONE()


