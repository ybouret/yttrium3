
//! \file

#ifndef Y_Chemical_SpRoll_Included
#define Y_Chemical_SpRoll_Included 1

#include "y/chemical/type/roll.hpp"
#include "y/chemical/species.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Roll<Species>   SpRoll;
        typedef AutoPtr<SpRoll> SpDB;
    }

}

#endif // !Y_Chemical_SpRoll_Included
