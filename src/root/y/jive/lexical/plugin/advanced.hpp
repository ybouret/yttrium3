
//! \file

#ifndef Y_Jive_Lexical_AdvancedPlugin_Included
#define Y_Jive_Lexical_AdvancedPlugin_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class AdvancedPlugin
            {
            public:
                
                virtual ~AdvancedPlugin() noexcept;
            private:
                Y_Disable_Copy_And_Assign(AdvancedPlugin);
            };
        }

    }
}

#endif // !Y_Jive_Lexical_AdvancedPlugin_Included
