#include "y/jive/lexical/plugin/bstring.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

           
            void BString:: init()
            {
                doChar('\"');
                doChar('\'');
            }

            BString:: ~BString() noexcept
            {

            }

        }

    }

}


