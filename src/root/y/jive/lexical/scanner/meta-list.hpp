
//! \file

#ifndef Y_Jive_Lexical_MetaList_Included
#define Y_Jive_Lexical_MetaList_Included 1

#include "y/jive/lexical/rule.hpp"
#include "y/handy/basic/light/list.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            typedef Handy::BasicLightList<const Rule> RList;

            class MetaList : public CountedObject, public RList
            {
            public:
                explicit MetaList() noexcept;
                virtual ~MetaList() noexcept;

            private:
                Y_Disable_Copy_And_Assign(MetaList);
            };
        }

    }
}
#endif // !Y_Jive_Lexical_MetaList_Included



