
#include "y/jive/editor.hpp"
#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"
#include "y/jive/lexical/plugin/multi-lines-comment.hpp"

using namespace Yttrium;

namespace {

    class WeaselParser : public Jive::Parser
    {
    public:

        explicit WeaselParser() : Jive:: Parser("Weasel")
        {

            Aggregate & WEASEL = agg(lang);



            load(TypeToType<Jive::Lexical::CxxComment>(),"CxxComment");
            load(TypeToType<Jive::Lexical::C_Comment>(),"C_Comment");
            drop("blank", "[:blank:]");
            endl("endl",  "[:endl:]");

            render();
        }


        virtual ~WeaselParser() noexcept
        {

        }

    private:
        Y_Disable_Copy_And_Assign(WeaselParser);
    };

}


Y_UTEST(jive_formula)
{
    WeaselParser weasel;
    
#if 0
    Eval eval;
    Jive::Editor edit(eval.lang);
    edit.verbose = true;

    if(argc>1)
    {
        AutoPtr<Jive::Syntax::XNode> tree = eval.getAST( Jive::Module::OpenFile(argv[1]) );
        {
            const String dotFile = *eval.lang + "-ast-tree.dot";
            Vizible::Render(dotFile,*tree,false);
        }
        std::cerr << std::endl;
        edit(tree,Jive::Tolerant);
    }
#endif

}
Y_UDONE()
