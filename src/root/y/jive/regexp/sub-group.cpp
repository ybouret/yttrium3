#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/posix.hpp"

namespace Yttrium
{

    namespace Jive
    {
        

        const char RXCompiler:: EscGroup[] = "[]\\^-:";


        Pattern * RXCompiler:: subGroup()
        {
            assert(LBRACK == curr[-1]);

            if(curr>=last) throw Specific::Exception(CallSign, "early end of sub-group in '%s'",expr);

            AutoPtr<Logic> g = 0;
            // check first char
            switch(*curr)
            {
                case ':': ++curr; return subPosix();

                default:
                    break;
            }

            throw Exception("not implemented yet");


        }

    }

}

