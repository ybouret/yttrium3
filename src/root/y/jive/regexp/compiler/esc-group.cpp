
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"
#include <cstring>

namespace Yttrium
{

    namespace Jive
    {
        const char RXCompiler:: EscGroup[] = "[]\\^-:";

        Pattern * RXCompiler:: escGroup()
        {
            if(curr>=last) throw Specific::Exception(CallSign,"unfinished sub-group #%u escape sequence in '%s'", igrp, expr);

            const char c = *(curr++);

            // test common
            {
                const char * const src = strchr(EscCommSource,c);
                if(src) return new Byte( (uint8_t) EscCommTarget[ (size_t)(src-EscCommSource)] );
            }

            // test for subExpr
            {
                const char * const src = strchr(EscGroup,c);
                if(src) return new Byte( (uint8_t)c );
            }

            // test for hexa
            if('x'==c) return escHexa();

            throw Specific::Exception(CallSign,
                                      "unknown sub-group #%u escaped char '%s' in '%s'",
                                      igrp,
                                      ASCII::Printable::Text(c),
                                      expr);


        }
    }

}

