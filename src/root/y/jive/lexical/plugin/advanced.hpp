
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
            //__________________________________________________________________
            //
            //
            //
            //! Advanced Plugin interface
            //
            //
            //__________________________________________________________________
            class AdvancedPlugin : public Plugin
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param id plugin name
                 \param rx calling expression
                 \param stk stack to store results
                 \param eos end of stream policy
                 */
                template <typename ID, typename RX> inline
                explicit AdvancedPlugin(const ID &  id,
                                        const RX &  rx,
                                        Stack    &  stk,
                                        const OnEOS eos) :
                Plugin(id,rx,eos),
                stack(stk)
                {
                }

                //! cxleanup
                virtual ~AdvancedPlugin() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
            public:
                void onEnter(Token &); //!< called on plugin enter
            private:
                void onLeave(Token &); //!< called on plugin leave, for backOn

            protected:

                //! helper to return from plugin with action
                /**
                 \param brx back expression
                 \param eol according to brx
                 */
                template <typename BACK_EXPR> inline
                void backOn(const BACK_EXPR &brx, const EndOfLineFlag eol)
                {
                    back(brx,eol,this, & AdvancedPlugin::onLeave );
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            protected:
                Stack &stack; //!< from lexer
                
            private:
                Y_Disable_Copy_And_Assign(AdvancedPlugin); //!< discarded

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void enter(Token&) = 0; //!< initialize plugin
                virtual void leave(Token&) = 0; //!< finalize plugin

            };
        }

    }
}

#endif // !Y_Jive_Lexical_AdvancedPlugin_Included
