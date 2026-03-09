//! \file

#ifndef Y_Libc_Sort_Included
#define Y_Libc_Sort_Included

#include "y/config/setup.h"

#if defined(__cplusplus)
extern "C" {
#endif

    typedef int (*YttriumCompare)(const void * const, const void * const);

    void Yttrium_Sort(void * const   a,
                      const size_t   n,
                      const size_t   width,
                      YttriumCompare compare,
                      void * const   rra);



#if defined(__cplusplus)
}
#endif


#endif // !Y_Libc_Sort_Included
