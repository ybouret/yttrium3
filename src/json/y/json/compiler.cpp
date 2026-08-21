
#include "y/json/compiler.hpp"
#include "y/jive/parser.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace JSON
    {

        const char * const Compiler:: CallSign = "JSON";

        class Compiler:: Code :
        public Jive::Parser
        {
        public:
            explicit Code();
            virtual ~Code() noexcept;
        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Compiler:: Code:: ~Code() noexcept {}

        Compiler:: Code:: Code() :
        Jive::Parser(CallSign)
        {
            Y_STATIC_CHECK( Y_Is_SuperSubClass_Strict(Object,Code), BadCode);

            
            // lexical only rules
            drop("blank", "[:blank:]");
            endl("endl",  "[:endl:]");
        }


        ////////////////////////////////////////////////////////////////////////

        Compiler:: Compiler() : code( new Code() )
        {
        }


        Compiler:: ~Compiler() noexcept
        {
            Destroy(code);
        }
    }
}
