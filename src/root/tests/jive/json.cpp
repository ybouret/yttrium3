#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"

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

        validate();
        render();
    }



}

Y_UTEST(jive_json)
{

    JParser json;

    if(argc>1)
    {
        AutoPtr<Jive::Syntax::XNode> tree = json.getAST( Jive::Module::OpenFile(argv[1]) );

    }

}
Y_UDONE()

