


//! \file

#ifndef Y_Chemical_SList_Included
#define Y_Chemical_SList_Included 1

#include "y/chemical/species.hpp"
#include "y/handy/basic/light/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Handy::BasicLightList<const Species> SList; //!< alias
        typedef SList::NodeType                      SNode; //!< alias
    }

}

#endif // !Y_Chemical_SList_Included

