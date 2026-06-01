
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/defs.hpp"
#include "y/stream/identifier.hpp"
#include "y/graphviz/vizible.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            class Rule : public Object, public Vizible
            {
            public:
                template <typename RID> inline
                explicit Rule(const RID &    ruleName,
                              const Kind     ruleKind,
                              const uint32_t ruleUUID) :
                name(ruleName),
                kind(ruleKind),
                uuid(ruleUUID),
                next(0)
                {
                }
                
                virtual ~Rule() noexcept;

                const char *   humanReadableKind() const noexcept;

                const Identifier name;
                const Kind       kind;
                const uint32_t   uuid;
                Rule *           next;
                
            private:
                Y_Disable_Copy_And_Assign(Rule);
            };

        }

    }

}

#endif // !Y_Jive_Syntax_Rule_Included

