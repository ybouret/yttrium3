

#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"

#include <cstring>

namespace Yttrium
{

    namespace Jive
    {

        const char RXCompiler:: EscCommSource[] = "nrtvfba";
        const char RXCompiler:: EscCommTarget[] = "\n\r\t\v\f\b\a";

        const char RXCompiler:: EscExpr[] = "()&*+?.\\[]{}";

        Pattern * RXCompiler:: escExpr()
        {
            if(curr>=last) throw Specific::Exception(CallSign,"unfinished sub-expression escape sequence in '%s'", expr);

            const char c = *(curr++);

            // test common
            {
                const char * const src = strchr(EscCommSource,c);
                if(src) return new Byte( EscCommTarget[ (size_t)(src-EscCommSource)] );
            }

            // test for subExpr
            {
                const char * const src = strchr(EscExpr,c);
                if(src) return new Byte( (uint8_t)c );
            }

            if('x'==c) return escHexa();

            throw Specific::Exception(CallSign,
                                      "unknown sub-expression escaped char '%s' in '%s'",
                                      ASCII::Printable::Text(c),
                                      expr);


        }
    }

}

