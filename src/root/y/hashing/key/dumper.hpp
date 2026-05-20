
//! \file

#ifndef Y_Hashing_Key_Dumper_Included
#define Y_Hashing_Key_Dumper_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Hashing
    {
        template <typename DST>
        struct Dumping
        {
            template <typename SRC> static
            DST From(const SRC &x) noexcept;
        };
    }

}

#endif // !Y_Hashing_Key_Dumper_Included
