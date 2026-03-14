
//! \file

#ifndef Y_Memory_Page_Included
#define Y_Memory_Page_Included 1


#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct Page
        {
            static const size_t   MinBytes = 2*sizeof(void*);
            static const unsigned MinShift = IntegerLog2<MinBytes>::Value;
            Page *next;
            Page *prev;
            static Page *From(void * const blockAddr) noexcept;
        };
    }

}

#endif // !Y_Memory_Page_Included
