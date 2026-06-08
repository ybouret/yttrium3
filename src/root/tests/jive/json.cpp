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
        Alternate &JSON = alt("JSON");
        validate();
        render();
    }



}

Y_UTEST(jive_json)
{

    JParser json;

}
Y_UDONE()

