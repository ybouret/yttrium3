
//! \file

#ifndef Y_Jive_Syntax_BookOfRules_Included
#define Y_Jive_Syntax_BookOfRules_Included 1


#include "y/container/associative/book.hpp"
#include "y/container/associative/hash/default-set.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            class Rule;

            typedef BookOf<const Rule,DefaultHashSet> BookOfRules; //!< alias


        }

    }

}


#endif // !Y_Jive_Syntax_BookOfRules_Included

