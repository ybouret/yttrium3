
#include "y/json/compiler.hpp"
#include "y/jive/parser.hpp"
#include "y/check/static.hpp"
#include "y/jive/lexical/plugin/jstring.hpp"

namespace Yttrium
{
    namespace JSON
    {

        const char * const Compiler:: CallSign = "JSON";

        namespace
        {
            static const char NumberRX[] =
            "[-+]?[:digit:]+";

        }


        class Compiler:: Code :
        public Jive::Parser
        {
        public:
            explicit Code();
            virtual ~Code() noexcept;

            void compile(Jive::Module * const);


        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Compiler:: Code:: ~Code() noexcept {}

        Compiler:: Code:: Code() :
        Jive::Parser(CallSign)
        {
            Y_STATIC_CHECK( Y_Is_SuperSubClass_Strict(Object,Code), BadCode);

            //------------------------------------------------------------------
            //
            //
            // top level
            //
            //
            //------------------------------------------------------------------
            Alternate  &JSON   = alt("JSON");
            Alternate  &VALUE  = alt("VALUE");
            const Rule &STRING = use( TypeToType<Jive::Lexical::JString>(), "STRING");

            //------------------------------------------------------------------
            //
            //
            // Arrays
            //
            //
            //------------------------------------------------------------------
            {
                const Rule &EMPTY_ARRAY = (agg("EMPTY_ARRAY") << '[' << ']');
                const Rule &HEAVY_ARRAY = (agg("HEAVY_ARRAY") << '[' << VALUE << extra(',',VALUE) << ']');
                const Rule &ARRAY       = (alt("ARRAY") << EMPTY_ARRAY << HEAVY_ARRAY);
                VALUE << ARRAY;
                JSON  << ARRAY;
            }

            //------------------------------------------------------------------
            //
            //
            // Objects
            //
            //
            //------------------------------------------------------------------
            {
                const Rule &PAIR         = (agg("PAIR") << STRING << ':' << VALUE);
                const Rule &EMPTY_OBJECT = (agg("EMPTY_OBJECT") << '{' << '}');
                const Rule &HEAVY_OBJECT = (agg("HEAVY_OBJECT") << '{' << PAIR << extra(',',PAIR) << '}');
                const Rule &OBJECT       = (alt("OBJECT") << EMPTY_OBJECT << HEAVY_OBJECT);
                VALUE << OBJECT;
                JSON  << OBJECT;
            }

            //------------------------------------------------------------------
            //
            //
            // gather value
            //
            //
            //------------------------------------------------------------------
            VALUE << STRING << term("NUMBER",NumberRX) << "true" << "false" << "null";

            //------------------------------------------------------------------
            //
            //
            // lexical only rules
            //
            //
            //------------------------------------------------------------------
            drop("blank", "[:blank:]");
            endl("endl",  "[:endl:]");

            //------------------------------------------------------------------
            //
            //
            // Validate
            //
            //
            //------------------------------------------------------------------
            validate();
        }


        void Compiler:: Code:: compile(Jive::Module *const m)
        {
            AutoPtr<XNode> ast = getAST(m);
            
        }

        ////////////////////////////////////////////////////////////////////////

        Compiler:: Compiler() : code( new Code() )
        {
        }


        Compiler:: ~Compiler() noexcept
        {
            Destroy(code);
        }

        void Compiler:: render() const
        {
            assert(code);
            code->render();
        }

        void Compiler:: operator()(Jive::Module * const m)
        {
            code->compile(m);


        }


    }
}
