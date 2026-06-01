//! \file

#ifndef Y_Jive_Syntax_Internal_Included
#define Y_Jive_Syntax_Internal_Included 1

#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            //__________________________________________________________________
            //
            //
            //
            //! Internal base class
            //
            //
            //__________________________________________________________________
            class Internal : public Rule
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
                 \param ruleName name
                 \param ruleUUID uuid
                 */
                template <typename ID> inline
                explicit Internal(const ID &     ruleName,
                                  const uint32_t ruleUUID) :
                Rule(ruleName,IsInternal,ruleUUID)
                {

                }

                virtual ~Internal() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(Internal); //!< discarded
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Internal_Included
