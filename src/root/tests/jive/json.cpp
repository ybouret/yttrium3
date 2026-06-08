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
        Alternate &JSON  = alt("JSON");
        Alternate &VALUE = alt("VALUE");

        {
            const Rule &EMPTY_ARRAY = (agg("EMPTY_ARRAY") << '{' << '}');
            const Rule &HEAVY_ARRAY = (agg("HEAVY_ARRAY") << '{' << VALUE << extra(',',VALUE) << '}');
            const Rule &ARRAY       = (alt("ARRAY") << EMPTY_ARRAY << HEAVY_ARRAY);
            VALUE << ARRAY;
            JSON  << ARRAY;
        }

        VALUE << term("NUMBER","[:digit:]+") << "true" << "false" << "null";

        validate();
        render();
    }



}

Y_UTEST(jive_json)
{

    JParser json;

}
Y_UDONE()

