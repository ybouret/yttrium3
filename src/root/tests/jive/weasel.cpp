
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

            // top level
            Aggregate  & WEASEL    = agg(lang);

            // lexical markers
            const Rule & BLANK     = mark("blank","[:blank:]");
            const Rule & NEWLINE   = newline("endl","[:endl:]");
            const Rule & BLANKS    = (grp("BLANKS") << zom( pick(BLANK,NEWLINE)));
            const Rule & END       = opt( mark(';') );

            const Rule & FRAG  = term("FRAG","[:upper:][:lower:]*");
            const Rule & COEF  = term("COEF","[:digit:]+");
            const Rule & OCOF  = opt(COEF);

            Aggregate & GRP  = yld("GRP");
            Aggregate & STO  = yld("STO");
            Alternate & NUB  = alt("NUB");
            GRP  << oom(STO);
            STO  << NUB << OCOF;
            NUB << FRAG << parens(GRP);

            const Rule & PLUS  = term('+');
            const Rule & MINUS = term('-');
            const Rule & SIGN  = alt("SIGN") << PLUS << MINUS;
            const Rule & Z     = agg("Z") << '^' << OCOF << SIGN;
            Compound   & SP    = (agg("SP") << GRP << opt(Z) );

            Alternate  & DECL = alt("DECL");

            DECL << SP;

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
