
#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"
#include "y/jive/lexical/plugin/multi-lines-comment.hpp"
#include "y/jive/lexical/plugin/verbatim.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/jive/lexical/plugin/rstring.hpp"
#include "y/jive/lexical/plugin/bstring.hpp"

using namespace Yttrium;

namespace
{

    class MyLexer : public Jive::Lexer
    {
    public:
        inline explicit MyLexer() : Jive::Lexer("MyLexer")
        {
            emit("ID","[:alpha:][:word:]+");
            emit("INT","[:digit:]+");
            load( TypeToType<Jive::Lexical::ShellComment>(), "shellComment");
            load( TypeToType<Jive::Lexical::C_Comment>(), "C_Comment");
            load( TypeToType<Jive::Lexical::SingleLineComment>(), "LuaComment", "--");

            dial( TypeToType<Jive::Lexical::Verbatim>(), "Verbatim");
            dial( TypeToType<Jive::Lexical::JString>(), "JString");
            dial( TypeToType<Jive::Lexical::RString>(), "RString");
            dial( TypeToType<Jive::Lexical::BString>(), "BString");


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
    Jive::Lexical::Scanner::Verbose = true;
    MyLexer lxr;

    if(argc>1)
    {
        Jive::Source   source( Jive::Module::OpenFile(argv[1]) );
        Jive::Lexemes  lxm;

        while( true )
        {
            Jive::Lexeme * const lx = lxr.pull(source);
            if(!lx) break;
            lxm.pushTail(lx);
        }
        std::cerr << "-- lexemes: " << std::endl;
        for(const Jive::Lexeme *lx=lxm.head;lx;lx=lx->next)
        {
            std::cerr << *lx << std::endl;
        }

    }
    

}
Y_UDONE()

