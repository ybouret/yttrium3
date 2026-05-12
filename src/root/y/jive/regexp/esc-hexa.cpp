
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"

#include "y/format/hexadecimal.hpp"

namespace Yttrium
{

    namespace Jive
    {

        Pattern * RXCompiler:: escHexa()
        {
            assert('x'==curr[-1]);
            if(curr>=last) throw Specific::Exception(CallSign, "missing hexadecimal code in '%s'",expr);

            const char up = *(curr++);
            if(curr>=last) throw Specific::Exception(CallSign, "unfinished hexadecimal in '%s'",expr);
            const char lo = *(curr++);

            const int upper = Hexadecimal::ToDec(up); if(upper<0) throw Specific::Exception(CallSign, "'%c' is not a xdigit in '%s'",up,expr);
            const int lower = Hexadecimal::ToDec(lo); if(lower<0) throw Specific::Exception(CallSign, "'%c' is not a xdigit in '%s'",lo,expr);

            return new Byte( (uint8_t)(upper*16+lower) );




            throw Specific::Exception(CallSign,"not implemented");

        }
    }

}

