
#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    class MyLexer : public Jive::Lexer
    {
    public:
        inline explicit MyLexer() : Jive::Lexer("MyLexer")
        {
        }


        inline virtual ~MyLexer() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };
}

Y_UTEST(jive_lexer)
{
    MyLexer lxr;
    
}
Y_UDONE()

