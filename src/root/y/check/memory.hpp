
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

        static const void * GetUpper(const void * const entry,
                                     const size_t       bytes,
                                     const size_t       blockSize) noexcept;


        template <typename T> static inline
        bool Inside(const void * const entry,
                    const size_t       bytes,
                    const T * const    address)  noexcept
        {
            assert(address);
            assert(bytes>=sizeof(T));
            const T * const lower = static_cast<const T *>(entry);
            if(address<lower)
                return false;
            const T * const upper = static_cast<const T *>(GetUpper(entry,bytes,sizeof(T)));
            if(address>upper)
                return false;
            return true;
        }

        template <typename T> static inline
        bool Inside(const void * const entry,
                    const size_t       bytes,
                    const T &          host)  noexcept
        {
            return Inside(entry,bytes,&host);
        }
    };

}


#endif // !Y_Check_Memory_Included

