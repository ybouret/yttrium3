#include "y/utest/run.hpp"
#include "y/libc/strlen.h"
#include <cassert>

namespace Yttrium {

    namespace UTest
    {
        size_t Display::Width = 32;

        std::ostream & Display:: Print(std::ostream &os,
                                       const char * const pfx,
                                       const char * const name,
                                       const char * const sfx)
        {
            const size_t len = Yttrium_Strlen(name);
            if(pfx)  os << pfx;
            if(name) os << name;
            if(sfx)  os << sfx;
            for(size_t i=len;i<Width;++i) os << ' ';
            return os;
        }

    }

}
