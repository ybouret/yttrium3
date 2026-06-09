
//! \file

#ifndef Y_Jive_Syntax_Expected_Included
#define Y_Jive_Syntax_Expected_Included 1


#include "y/container/associative/book.hpp"
#include "y/container/associative/hash/default-set.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            class Rule;

            typedef BookOf<const Rule,DefaultHashSet> BookOfRules;

            class Expected : public Object, public BookOfRules
            {
            public:
                explicit Expected();
                virtual ~Expected() noexcept;
            private:
                Y_Disable_Copy_And_Assign(Expected);
            };

        }

    }

}


#endif // !Y_Jive_Syntax_Expected_Included

