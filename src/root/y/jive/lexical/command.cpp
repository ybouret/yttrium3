
#include "y/jive/lexical/command.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Command:: Command() noexcept : kind(Quit), args(0) {}
            Command:: ~Command() noexcept
            {
                Coerce(kind) = Quit;
                Coerce(args) = 0;
            }
        }

    }

}


