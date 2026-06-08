
#include "y/jive/lexical/plugin/jstring.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            void JString:: init()
            {
                doChar('\'');
                doChar('<');
                doChar('>');
            }

            JString:: ~JString() noexcept
            {
            }
            
        }

    }

}


