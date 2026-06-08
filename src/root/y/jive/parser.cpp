
#include "y/jive/parser.hpp"


namespace Yttrium
{
    namespace Jive
    {

        Parser:: ~Parser() noexcept
        {
            
        }

        const Syntax::Rule & Parser:: mark(const char c)
        {
            return mark(c,c);
        }


    }

}

