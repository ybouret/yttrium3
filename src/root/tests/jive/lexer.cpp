
#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"
#include "y/jive/lexical/plugin/multi-lines-comment.hpp"

using namespace Yttrium;
#if 0
namespace
{

    class MyLexer : public Jive::Lexer
    {
    public:
        inline explicit MyLexer() : Jive::Lexer("MyLexer")
        {
            emit("ID","[:alpha:][:word:]+");
            load( TypeToType<Jive::Lexical::ShellComment>(), "shellComment");
            load( TypeToType<Jive::Lexical::C_Comment>(), "C_Comment");
            drop("blank","[:blank:]");
            endl("endl","[:endl:]");
        }


        inline virtual ~MyLexer() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };
}
#endif

Y_UTEST(jive_lexer)
{
#if 0
    MyLexer lxr;

    if(argc>1)
    {
        Jive::Source   source( Jive::Module::OpenFile(argv[1]) );
        Jive::Lexemes  lxm;

        while( true )
        {
            Jive::Lexeme * const lx = lxr.get(source);
            if(!lx) break;
            lxm.pushTail(lx);
            std::cerr << *lx << std::endl;
        }


    }
#endif
    

}
Y_UDONE()

