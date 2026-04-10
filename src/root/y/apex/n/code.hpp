
//! \file

#ifndef Y_Apex_Natural_Code_Included
#define Y_Apex_Natural_Code_Included 1

#include "y/apex/natural.hpp"
#include "y/apex/k/keg.hpp"

namespace Yttrium
{
    namespace Apex
    {
        struct KegInfo
        {
            typedef uint32_t WordType;
            typedef uint64_t CoreType;
        };

        typedef Keg<KegInfo::WordType> KegType;

        

    }

}
#endif // !Y_Apex_Natural_Code_Included
