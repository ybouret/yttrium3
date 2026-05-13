//! \file

#ifndef Y_Libc_PQ_Included
#define Y_Libc_PQ_Included

#include "y/libc/compare.h"

#if defined(__cplusplus)
extern "C" {
#endif

    
    //! balance after push at numBlock-1
    /**
     \param blockAddr address of first item
     \param numBlocks number of items
     \param blockSize bytes per item
     \param compare   comparison
     \param args      for compare
     */
    void Yttrium_PQ_Push_Balance(void * const   blockAddr,
                                 const size_t   numBlocks,
                                 const size_t   blockSize,
                                 YttriumCompare compare,
                                 void * const   args);

    //! balance after pull at 0
    /**
     \param blockAddr address of first item
     \param numBlocks number of items
     \param blockSize bytes per item
     \param compare   comparison
     \param args      for compare
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
