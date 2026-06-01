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

            class Internal : public Rule
            {
            public:

                template <typename ID> inline
                explicit Internal(const ID &     ruleName,
                                  const uint32_t ruleUUID) :
                Rule(ruleName,IsInternal,ruleUUID)
                {

                }

                virtual ~Internal() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Internal);
            };
        }

    }

}

#endif // !Y_Jive_Syntax_Internal_Included
