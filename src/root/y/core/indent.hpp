//! \file

#ifndef Y_Core_Indent_Included
#define Y_Core_Indent_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Core
    {
        template <typename OSTREAM> inline
        OSTREAM & Indent(OSTREAM &os, size_t level, const char c = ' ')
        {
            while(level-- > 0 ) os << c;
            return os;
        }
    }
}

#endif // !Y_Core_Indent_Included

