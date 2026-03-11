
//! \file

#ifndef Y_Memory_Ownership_Included
#define Y_Memory_Ownership_Included 1

#include "y/config/compiler.h"
#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //! Helper for memory location
        //
        //______________________________________________________________________
        enum Ownership
        {
            OwnedByPrev, //!< memory is previous container
            OwnedBySelf, //!< memory is in this container
            OwnedByNext  //!< memory is in next container
        };
        
    }

}

#endif // !Y_Memory_Ownership_Included
