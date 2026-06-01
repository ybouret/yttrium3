
//! \file

#ifndef Y_Jive_Syntax_Wildcard_Included
#define Y_Jive_Syntax_Wildcard_Included 1

#include "y/jive/syntax/rule/internal.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            class Wildcard : public Internal
            {
            public:
                template <typename ID>
                explicit Wildcard(const ID      & ruleName,
                                  const uint32_t  ruleUUID,
                                  const Rule    & source) :
                Internal(ruleName,ruleUUID),
                rule(source)
                {
                }


                virtual ~Wildcard() noexcept;

                virtual OutputStream & vizLink(OutputStream &) const;

                const Rule &rule;

            private:
                Y_Disable_Copy_And_Assign(Wildcard);
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Wildcard_Included
