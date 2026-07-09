
//! \file

#ifndef Y_Chemical_SpRoll_Included
#define Y_Chemical_SpRoll_Included 1

#include "y/chemical/type/roll.hpp"
#include "y/chemical/species.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Roll<const Species>   SpRoll; //!< alias
        typedef AutoPtr<SpRoll> SpDB;   //!< alias
    }

}

#endif // !Y_Chemical_SpRoll_Included
