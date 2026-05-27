#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Plugin:: ~Plugin() noexcept
            {
            }

#if 0
            void Plugin:: enter()
            {
                std::cerr << "Enter <" << name << ">" << std::endl;
            }

            void Plugin:: leave()
            {
                std::cerr << "Leave <" << name << ">" << std::endl;

            }
#endif
        }

    }
}

