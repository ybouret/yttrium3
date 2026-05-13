//! \file

#ifndef Y_Libc_PQ_Included
#define Y_Libc_PQ_Included

#include "y/libc/compare.h"

#if defined(__cplusplus)
extern "C" {
#endif


    //! balance after insertion at numBlock-1
    void Yttrium_PQ_Balance(void * const   blockAddr,
                            const size_t   numBlocks,
                            const size_t   blockSize,
                            YttriumCompare compare,
                            void * const   args);

#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_PQ_Included
