

//! \file

#ifndef Y_Chemical_EList_Included
#define Y_Chemical_EList_Included 1

#include "y/chemical/reactive/equilibrium.hpp"
#include "y/handy/basic/light/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Handy::BasicLightList<Equilibrium> EList; //!< alias
        typedef EList::NodeType                    ENode; //!< alias
    }

}

#endif // !Y_Chemical_EList_Included

