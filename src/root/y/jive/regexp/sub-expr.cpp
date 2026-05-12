
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{

    namespace Jive
    {
        Pattern * RXCompiler:: subExpr()
        {
            if(curr>=last) throw Specific::Exception(CallSign, "empty sub-expression in '%s'",expr);
            AutoPtr<Logic> p = new And();

            while(curr<last)
            {
                const char c = *(curr++);

                switch(c)
                {
                    default:
                        *p << (uint8_t)c;
                }
            }

            return p.yield();
        }

    }

}

