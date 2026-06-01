
#include "y/jive/lexical/plugin/advanced.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            AdvancedPlugin:: ~AdvancedPlugin() noexcept
            {
            }

            void AdvancedPlugin:: onEnter(Token &ini)
            {
                Y_Jive_Lexical(name << ".enter('" << ini << "')");
                enter(ini);
            }

            void AdvancedPlugin:: onLeave(Token &end)
            {
                Y_Jive_Lexical(name << ".leave('" << end << "')");
                leave(end);
            }
            

        }


    }
}

