#include "y/jive/syntax/grammar.hpp"

#include "y/jive/lexical/plugin/single-line-comment.hpp"
#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/rule/terminal.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{

    class MyLexer : public Lexer
    {
    public:

        explicit MyLexer() : Lexer("MyLexer")
        {
            emit("ID","[:alpha:][:word:]+");
            emit("INT","[:digit:]+");
            drop("blank","[:blank:]");
            endl("endl","[:endl:]");
            load( TypeToType<Jive::Lexical::ShellComment>(), "COM");
        }

        virtual ~MyLexer() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };

    class MyGrammar : public Syntax::Grammar
    {
    public:
        explicit MyGrammar() : Syntax:: Grammar("MyGrammar")
        {
            const Rule & ID  = trm("ID");
            const Rule & IDS = oom(ID);
            topLevel(IDS);
        }

        virtual ~MyGrammar() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(MyGrammar);
    };

}

Y_UTEST(jive_grammar)
{
    MyLexer   L;
    MyGrammar G;

    G.render();
    G.validate();

}
Y_UDONE()

