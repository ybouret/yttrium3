
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

            Aggregate  & WEASEL    = agg(lang);
            const Rule & BLANK     = mark("blank","[:blank:]");
            const Rule & NEWLINE   = newline("endl","[:endl:]");
            const Rule & BLANKS    = (grp("BLANKS") << zom( pick(BLANK,NEWLINE)));
            const Rule & FRAGMENT  = term("FRAGMENT","[:upper:][:alpha:]*");
            const Rule & END       = opt( mark(';') );
            Alternate  & DECL      = alt("DECL");
            DECL << FRAGMENT;
            Aggregate  & STATEMENT = yld("STATEMENT");
            STATEMENT << BLANKS << DECL << BLANKS << END;

            WEASEL << zom(STATEMENT) << BLANKS;




            load(TypeToType<Jive::Lexical::CxxComment>(),"CxxComment");
            load(TypeToType<Jive::Lexical::C_Comment>(),"C_Comment");

            render();
        }


        virtual ~WeaselParser() noexcept
        {

        }

    private:
        Y_Disable_Copy_And_Assign(WeaselParser);
    };

}


Y_UTEST(jive_weasel)
{
    WeaselParser weasel;
    
    Jive::Editor edit(weasel.lang);
    edit.verbose = true;

    if(argc>1)
    {
        AutoPtr<Jive::Syntax::XNode> tree = weasel.getAST( Jive::Module::OpenFile(argv[1]) );
        {
            const String dotFile = *weasel.lang + "-ast-tree.dot";
            Vizible::Render(dotFile,*tree,false);
        }
        std::cerr << std::endl;
        edit(tree,Jive::Tolerant);
    }

}
Y_UDONE()
