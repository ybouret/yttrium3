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

    //__________________________________________________________________________
    //
    //! Co-heap-sort anonymous arrays
    /**
     \param a       base address of items
     \param n       number of items
     \param wa      bytes per item of a
     \param compare comparison function
     \param args    comparison extra arguments
     \param rra     extra memory of at least wa bytes
     \param b       base address of co-items
     \param wb      bytes per item of b
     \param rrb     extra memory of at least wb bytes
     */
    //__________________________________________________________________________
    void Yttrium_CoSort(void * const   a,
                        const size_t   n,
                        const size_t   wa,
                        YttriumCompare compare,
                        void * const   args,
                        void * const   rra,
                        void * const   b,
                        const size_t   wb,
                        void * const   rrb);


#if defined(__cplusplus)
}
#endif


#endif // !Y_Libc_Sort_Included
