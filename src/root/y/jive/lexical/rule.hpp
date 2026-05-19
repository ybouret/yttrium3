
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Rule : public Object
        {
        public:


            virtual ~Rule() noexcept;

            const Identifier name;
            const Motif      motif;
            Rule *           next;
            Rule *           prev;
        private:
            Y_Disable_Copy_And_Assign(Rule);
        };
    }
}

#endif // !Y_Jive_Lexical_Rule_Included

