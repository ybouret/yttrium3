#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/type/conversion.hpp"

using namespace Yttrium;

namespace
{
    static inline
    void show(const String s)
    {
        std::cerr << '#' << std::setw(3) << s.size() << "/" << std::setw(3) << s.capacity() << ":[" << s << "]" << std::endl;
    }
}
Y_UTEST(string)
{
    Y_SIZEOF(Core::String<char>);
    Y_SIZEOF(Core::String<uint32_t>);

    const char little[] = " Hello ";
    const char big[] = " A really big string that neeeds a lot of characters to build ";

    { String s = little; show(s); }
    { String s = big;    show(s); }

    {
        const String a = little;
        const String b = big;
        show(a+b);
        show(b+a);
        show(a+big);
        show(little+b);
        show(a+'!');
        show('>'+a);
    }

    {
        String a = little;  show(a);
        a += little;        show(a);
        a += '!';           show(a);
        a += a;             show(a);
    }

    

}
Y_UDONE()

