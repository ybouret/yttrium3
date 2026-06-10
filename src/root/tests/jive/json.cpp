#include "y/jive/editor.hpp"
#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{

    class JParser : public Jive::Parser
    {
    public:
        explicit JParser();
        virtual ~JParser() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(JParser);
    };

    JParser:: JParser() : Jive::Parser("JSON")
    {
        Alternate  &JSON   = alt("JSON");
        Alternate  &VALUE  = alt("VALUE");
        const Rule &STRING = use( TypeToType<Jive::Lexical::JString>(), "STRING");

        {
            const Rule &EMPTY_ARRAY = (agg("EMPTY_ARRAY") << '[' << ']');
            const Rule &HEAVY_ARRAY = (agg("HEAVY_ARRAY") << '[' << VALUE << extra(',',VALUE) << ']');
            const Rule &ARRAY       = (alt("ARRAY") << EMPTY_ARRAY << HEAVY_ARRAY);
            VALUE << ARRAY;
            JSON  << ARRAY;
        }

        {
            const Rule &PAIR         = (agg("PAIR") << STRING << ':' << VALUE);
            const Rule &EMPTY_OBJECT = (agg("EMPTY_OBJECT") << '{' << '}');
            const Rule &HEAVY_OBJECT = (agg("HEAVY_OBJECT") << '{' << PAIR << extra(',',PAIR) << '}');
            const Rule &OBJECT       = (alt("OBJECT") << EMPTY_OBJECT << HEAVY_OBJECT);
            VALUE << OBJECT;
            JSON  << OBJECT;
        }

        VALUE << STRING << term("NUMBER","[:digit:]+") << "true" << "false" << "null";

        drop("blank", "[:blank:]");
        endl("endl",  "[:endl:]");

        validate();
        render();
    }

    class JEdit : public Jive::Editor
    {
    public:
        explicit JEdit(const JParser &jp) :
        Jive::Editor(jp.lang), strings()
        {
            Y_Jive_OnTerminal(JEdit,STRING);
        }



        virtual ~JEdit() noexcept {}

        Vector<String> strings;

    private:
        Y_Disable_Copy_And_Assign(JEdit);

        void onSTRING(const Lexeme &lx)
        {
            strings << lx.str();
            std::cerr << "strings=" << strings << std::endl;
        }


    };


}

Y_UTEST(jive_json)
{

    Jive::Lexical::Scanner::Verbose = true;
    Jive::Syntax::Rule::Verbose     = true;
    JParser      json;
    JEdit        edit(json);
    edit.verbose = true;

    if(argc>1)
    {
        AutoPtr<Jive::Syntax::XNode> tree = json.getAST( Jive::Module::OpenFile(argv[1]) );
        {
            const String dotFile = *json.lang + "-ast-tree.dot";
            Vizible::Render(dotFile,*tree,false);
        }
        std::cerr << std::endl;
        edit(tree,Jive::Tolerant);
    }

}
Y_UDONE()

