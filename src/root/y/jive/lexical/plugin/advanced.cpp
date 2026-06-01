
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

            void AdvancedPlugin:: onEnter(const Token &ini)
            {
                Y_Jive_Lexical(name << ".enter('" << ini << "')");
            }

            void AdvancedPlugin:: onLeave(const Token &end)
            {
                Y_Jive_Lexical(name << ".leave('" << end << "')");
                
            }


        }


    }
}

