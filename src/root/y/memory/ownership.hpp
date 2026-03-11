
//! \file

#ifndef Y_Memory_Ownership_Included
#define Y_Memory_Ownership_Included 1

#include "y/config/compiler.h"
#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        enum Ownership
        {
            OwnedByPrev,
            OwnedBySelf,
            OwnedByNext
        };
        
    }

}

#endif // !Y_Memory_Ownership_Included
