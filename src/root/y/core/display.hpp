//! \file

#ifndef Y_Core_Display_Included
#define Y_Core_Display_Included 1

#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //! vector-like display of a range
        /**
         \param os output stream
         \param iter initial iterator
         \param size number of elements
         \return os
         */
        //______________________________________________________________________
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


        //______________________________________________________________________
        //
        //! vector-like display of a range
        /**
         \param os output stream
         \param iter initial iterator
         \param size number of elements
         \return os
         */
        //______________________________________________________________________
        template <typename ITER, typename PROC> inline
        std::ostream & Display(std::ostream &os, ITER iter, size_t size, PROC &proc)
        {
            os << '[';
            if(size>0)
            {
                os << proc(*iter);
                while(--size>0)
                    os << ';' << proc(*(++iter));
            }
            return os << ']';
        }

    }
}

#endif // !Y_Core_Display_Included
