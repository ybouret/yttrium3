

//! \file

#ifndef Y_BZ2_Error_Included
#define Y_BZ2_Error_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace BZ2
    {
        struct Error
        {
            static const char * Get(const int bzerror) noexcept;

        };
    }

}

#endif // !Y_BZ2_Error_Included
