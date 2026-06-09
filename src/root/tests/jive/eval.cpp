
#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            Y_Jive_Single_Line_Comment(CxxComment, "//");
        }
    }
}

namespace
{
    /*
     add  : mult ('+'^ mult)* ; // left association
     mult : pow ('*'^ pow)* ; // left association
     pow  : atom ('^'^ pow)? ; // right association
     atom : ID | INT | '('^ add ')'! ; // recursion
     */
    class Eval : public Jive::Parser
    {
    public:

        explicit Eval() : Jive::Parser("Eval")
        {
            Compound &EVAL  = agg("EVAL");
            Compound &ADDOP = agg("ADDOP");
            Compound &MULOP = agg("MULOP");
            Compound &POW   = agg("POW");
            Compound &ATOM  = alt("ATOM");

            EVAL << zom(ADDOP);

            ADDOP << MULOP << zom(cat(pick( term('+'), term('-') ),MULOP));
            MULOP << POW   << zom(cat(pick( term('*'), term('/') ),POW));
            POW   << ATOM  << opt( cat( term('^'), POW) );
            ATOM  << term("ID","[:alpha:][:word:]*") << term("INT","[:digit:]+") << parens(ADDOP);


            load(TypeToType<Jive::Lexical::CxxComment>(),"CxxComment");
            drop("blank", "[:blank:]");
            endl("endl",  "[:endl:]");

            render();
        }

        virtual ~Eval() noexcept
        {
        }
    private:
        Y_Disable_Copy_And_Assign(Eval);
    };
}

Y_UTEST(jive_eval)
{
    Eval eval;
    
    if(argc>1)
    {
        AutoPtr<Jive::Syntax::XNode> tree = eval.getAST( Jive::Module::OpenFile(argv[1]) );
        {
            const String dotFile = *eval.lang + "-ast-tree.dot";
            Vizible::Render(dotFile,*tree,false);
        }
    }

}
Y_UDONE()
