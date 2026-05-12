//! \file

#ifndef Y_Jive_RegExp_Included
#define Y_Jive_RegExp_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Dictionary;

        struct RegExp
        {

            template <typename STRING> static inline
            Pattern * Compile(const STRING &data, const Dictionary * const dict)
            {
                const Identifier content(data);
                return Compile_(content,dict);
            }

        private:
            static Pattern * Compile_(const Identifier &,const Dictionary * const);
        
        };
    }

}
#endif // !Y_Jive_RegExp_Included

