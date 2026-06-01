
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

            class AdvancedPlugin : public Plugin
            {
            public:
                template <typename ID, typename RX> inline
                explicit AdvancedPlugin(const ID &  id,
                                        const RX &  rx,
                                        Stack    &  stk,
                                        const OnEOS eos) :
                Plugin(id,rx,eos),
                stack(stk)
                {
                }

                virtual ~AdvancedPlugin() noexcept;

                void onEnter(const Token &);

            protected:
                Stack &stack;

                template <typename BACK_EXPR> inline
                void backOn(const BACK_EXPR &brx, const EndOfLineFlag eol)
                {
                    back(brx,eol,this, & AdvancedPlugin::onLeave );
                }

            private:
                Y_Disable_Copy_And_Assign(AdvancedPlugin);
                void onLeave(const Token &);
            };
        }

    }
}

#endif // !Y_Jive_Lexical_AdvancedPlugin_Included
