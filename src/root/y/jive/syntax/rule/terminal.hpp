

//! \file

#ifndef Y_Jive_Syntax_Terminal_Included
#define Y_Jive_Syntax_Terminal_Included 1

#include "y/jive/syntax/rule.hpp"
#include "y/type/fourcc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            //__________________________________________________________________
            //
            //! role of the terminal
            //__________________________________________________________________
            enum Role
            {
                Semantic, //!< meaningful
                Dividing  //!< meaningless
            };

            //__________________________________________________________________
            //
            //! load of the terminal
            //__________________________________________________________________
            enum Load
            {
                Standard, //!< multiple forms
                Univocal  //!< single form
            };

            //__________________________________________________________________
            //
            //
            //
            //! Terminal rule
            //
            //
            //__________________________________________________________________
            class Terminal : public Rule
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('T','E','R','M'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param ruleName name
                 \param ruleRole role
                 \param ruleLoad load
                 */
                template <typename ID> inline
                explicit Terminal(const ID & ruleName,
                                  const Role ruleRole = Semantic,
                                  const Load ruleLoad = Standard) :
                Rule(ruleName,IsTerminal,UUID),
                role(ruleRole),
                load(ruleLoad)
                {

                }

                virtual ~Terminal() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizSelf(OutputStream &) const;
                Y_Jive_Syntax_Rule_Decl(); //!< accepts
                
                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Role role; //!< role
                const Load load; //!< load

            private:
                Y_Disable_Copy_And_Assign(Terminal); //!< discarded
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Terminal_Included
