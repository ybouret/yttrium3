

//! \file

#ifndef Y_Chemical_EqRoll_Included
#define Y_Chemical_EqRoll_Included 1

#include "y/chemical/type/roll.hpp"
#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Roll<Equilibrium> EqRoll; //!< alias
        typedef AutoPtr<EqRoll>   EqDB;   //!< alias
    }

}

#endif // !Y_Chemical_EqRoll_Included
