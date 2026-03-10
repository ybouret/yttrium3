//! \file

#ifndef Y_Libc_Sort_Included
#define Y_Libc_Sort_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    //! comparison function prototype
    typedef int (*YttriumCompare)(const void * const, const void * const, void * const);

    //__________________________________________________________________________
    //
    //! heap-sort anonymous array
    /**
     \param a       base address of items
     \param n       number of items
     \param width   bytes per item
     \param compare comparison function
     \param args    comparison extra arguments
     \param rra     extra memory of at least width bytes
     */
    //__________________________________________________________________________
    void Yttrium_Sort(void * const   a,
                      const size_t   n,
                      const size_t   width,
                      YttriumCompare compare,
                      void * const   args,
                      void * const   rra);



#if defined(__cplusplus)
}
#endif


#endif // !Y_Libc_Sort_Included
