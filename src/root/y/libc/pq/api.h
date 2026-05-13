//! \file

#ifndef Y_Libc_PQ_Included
#define Y_Libc_PQ_Included

#include "y/libc/compare.h"

#if defined(__cplusplus)
extern "C" {
#endif

    
    //! balance after push at numBlock-1
    /**

     */
    void Yttrium_PQ_Push_Balance(void * const   blockAddr,
                                 const size_t   numBlocks,
                                 const size_t   blockSize,
                                 YttriumCompare compare,
                                 void * const   args);

    //! balance after pull at 0
    /**
     
     */
    void Yttrium_PQ_Pull_Balance(void * const   blockAddr,
                                 const size_t   numBlocks,
                                 const size_t   blockSize,
                                 YttriumCompare compare,
                                 void * const   args);
#if defined(__cplusplus)
}
#endif



#endif // !Y_Libc_PQ_Included
