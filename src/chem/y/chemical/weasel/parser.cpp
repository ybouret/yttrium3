
#include "y/chemical/weasel/parser.hpp"
#include "y/jive/lexical/plugin/single-line-comment.hpp"
#include "y/jive/lexical/plugin/multi-lines-comment.hpp"
#include "y/jive/lexical/plugin/rstring.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Weasel:: Parser:: ~Parser() noexcept
        {
        }


        Weasel:: Parser:: Parser() :
        Jive::Parser(CallSign),
        formula( agg(Formula::CallSign) )
        {
            //------------------------------------------------------------------
            //
            //
            // top level
            //
            //
            //------------------------------------------------------------------
            Aggregate  & WEASEL    = agg(lang); topLevel(WEASEL);

            //------------------------------------------------------------------
            //
            //
            // lexical markers
            //
            //
            //------------------------------------------------------------------
            const Rule & BLANK     = mark("blank","[:blank:]");
            const Rule & NEWLINE   = newline("endl","[:endl:]");
            const Rule & BLANKS    = (grp("BLANKS") << zom( pick(BLANK,NEWLINE)));
            const Rule & END       = opt( mark(';') );

            // Formula grammar
            const Rule & FRAG  = term("FRAG","[:upper:][:lower:]*");
            const Rule & COEF  = term("COEF","[:digit:]+");
            const Rule & OCOF  = opt(COEF);

            Aggregate & GRP  = yld("GRP");
            Aggregate & STO  = yld("STO");
            Alternate & NUB  = alt("NUB");
            GRP  << oom(STO);
            STO  << NUB << OCOF;
            NUB << FRAG << parens(GRP);

            const Rule & PLUS    = term('+');
            const Rule & MINUS   = term('-');
            const Rule & SIGN    = alt("SIGN") << PLUS << MINUS;
            const Rule & Z       = agg("Z") << '^' << OCOF << SIGN;
            Coerce(formula) << GRP << opt(Z);

            //------------------------------------------------------------------
            //
            //
            // Statements, starting with formula
            //
            //
            //------------------------------------------------------------------
            Alternate  & DECL = alt("DECL");

            DECL << formula;

            Aggregate  & STATEMENT = yld("STATEMENT");
            STATEMENT << BLANKS << DECL << BLANKS << END;

            WEASEL << zom(STATEMENT) << BLANKS;

            //------------------------------------------------------------------
            //
            //
            // Equilibrium grammar
            //
            //
            //------------------------------------------------------------------
            Aggregate & EQ = agg("EQ");
            EQ << term("EID","@[:word:]+") << BLANKS << ':' << BLANKS;
            const Rule &ACTOR  = (agg("ACTOR") << BLANKS << OCOF << BLANKS << formula << BLANKS);
            const Rule &ACTORS = grp("ACTORS") << ACTOR << zom( cat(PLUS,ACTOR) );
            const Rule &OACTRS = opt(ACTORS);
            const Rule &REAC   = agg("REAC") << OACTRS;
            const Rule &PROD   = agg("PROD") << OACTRS;
            const Rule &KSTR   = use( TypeToType<Jive::Lexical::RString>(), "KSTR");
            EQ << REAC << BLANKS << mark("<=>") << BLANKS << PROD << BLANKS << ':' << BLANKS << KSTR;


            DECL << EQ;

            //------------------------------------------------------------------
            //
            //
            // Finalize
            //
            //
            //------------------------------------------------------------------
            load(TypeToType<Jive::Lexical::CxxComment>(),"CxxComment");
            load(TypeToType<Jive::Lexical::C_Comment>(),"C_Comment");

            render();
            validate();
        }

    }

}


