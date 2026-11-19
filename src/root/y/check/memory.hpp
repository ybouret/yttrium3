
//! \file

#ifndef Y_Check_Memory_Included
#define Y_Check_Memory_Included 1

#include "y/config/compiler.h"
#include <cassert>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Helper to check memory within region
    //
    //
    //__________________________________________________________________________
    struct CheckMemory
    {
        //! check object with array
        /**
         \param blockAddr first block address
         \param numBlocks number of blocks
         \param pObject   valid object address
         \return true iff pObject within block
         */
        template <typename T> static inline
        bool  Within(const T * const    blockAddr,
                     const size_t       numBlocks,
                     const T    * const pObject) noexcept
        {
            assert(pObject);
            return (pObject>=blockAddr) && (pObject<blockAddr+numBlocks);
        }


        //! upper object address from memory area
        /**
         \param  entry memory address
         \param  bytes memory length
         \param  blockSize size of object
         \return (entry+bytes)-blockSize
         */
        static const void * GetUpper(const void * const entry,
                                     const size_t       bytes,
                                     const size_t       blockSize) noexcept;


        //! check object with memory area
        /**
         \param  entry memory address
         \param  bytes memory length
         \param  address valid object addres
         \return true iff address inside memory area
         */
        template <typename T> static inline
        bool  Inside(const void * const entry,
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

    };

}


#endif // !Y_Check_Memory_Included

