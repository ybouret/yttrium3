
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
            typedef Handy::BasicLightList<const Rule> RList;    //!< alias
            typedef RList::NodeType                   MetaNode; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! list of rules with same leading char
            //
            //
            //__________________________________________________________________
            class MetaList : public CountedObject, public RList
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit MetaList() noexcept; //!< setup
                virtual ~MetaList() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(MetaList); //!< discarded
            };
        }

    }
}
#endif // !Y_Jive_Lexical_MetaList_Included



