//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        struct Convert
        {
            static const char * const CallSign;
            
            static uint64_t ToU64(const char *       text,
                                  const size_t       size,
                                  const char * const varName,
                                  const char * const varPart);
        };

    }

}

#endif // !Y_ASCII_Convert_Included
