
#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"

using namespace Yttrium;

namespace
{

    class MyLexer : public Jive::Lexer
    {
    public:
        inline explicit MyLexer() : Jive::Lexer("MyLexer")
        {
            emit("ID","[:alpha:][:word:]+");
            drop("blank","[:blank:]");
            endl("endl","[:endl:]");
        }


        inline virtual ~MyLexer() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };
}

Y_UTEST(jive_lexer)
{
    MyLexer lxr;

    if(argc>1)
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        
    }


}
Y_UDONE()

