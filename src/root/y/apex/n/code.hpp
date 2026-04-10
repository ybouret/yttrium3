
//! \file

#ifndef Y_Apex_Natural_Code_Included
#define Y_Apex_Natural_Code_Included 1

#include "y/apex/natural.hpp"
#include "y/apex/k/keg.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //! system Keg setup
        struct KegInfo
        {
            typedef uint32_t WordType; //!< alias
            typedef uint64_t CoreType; //!< alias
        };

        typedef Keg<KegInfo::WordType> KegType; //!< alias

        

    }

}
#endif // !Y_Apex_Natural_Code_Included
