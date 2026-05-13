#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/posix.hpp"

namespace Yttrium
{

    namespace Jive
    {
        



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
                    g = new Or();
                    break;
            }

            while(curr<last)
            {
                const char c = *(curr++);

                switch(c)
                {
                    case RBRACK:
                        goto RETURN;

                    default:
                        *g << (uint8_t)c;
                }
                
            }

            throw Specific::Exception(CallSign,"unfinished sub-group in '%s'", expr);

        RETURN:
            if(g->size<=0) throw Specific::Exception(CallSign,"empty sub-group in '%s'",expr);
            return g.yield();
        }

    }

}

