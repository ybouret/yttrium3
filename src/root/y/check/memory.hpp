
//! \file

#ifndef Y_Check_Memory_Included
#define Y_Check_Memory_Included 1

#include "y/config/compiler.h"
#include <cassert>

namespace Yttrium
{

    struct CheckMemory
    {
        template <typename T> static inline
        bool Within(const T * const    blockAddr,
                    const size_t       numBlocks,
                    const T    * const pObject) noexcept
        {
            assert(pObject);
            return (pObject>=blockAddr) && (pObject<blockAddr+numBlocks);
        }

        template <typename T> static inline
        bool Within(const T * const    blockAddr,
                    const size_t       numBlocks,
                    const T &          host) noexcept
        {
            return Within(blockAddr,numBlocks,&host);
        }

    };

}


#endif // !Y_Check_Memory_Included

