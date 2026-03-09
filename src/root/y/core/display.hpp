//! \file

#ifndef Y_Core_Display_Included
#define Y_Core_Display_Included 1

#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        template <typename ITER> inline
        std::ostream & Display(std::ostream &os, ITER iter, size_t size)
        {
            os << '[';
            if(size>0)
            {
                os << *iter;
                while(--size>0)
                    os << ';' << *(++iter);
            }
            return os << ']';
        }

    }
}

#endif // !Y_Core_Display_Included
