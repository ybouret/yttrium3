//! \file

#ifndef Y_Jive_RegExp_Included
#define Y_Jive_RegExp_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Dictionary;

        //______________________________________________________________________
        //
        //
        //
        //! Regular Expression compilation
        //
        //
        //______________________________________________________________________
        struct RegExp
        {
            //__________________________________________________________________
            //
            // Compile any expression to matching pattern
            /**
             \param data string, text, char, Identifier...
             \param dict optional dictionary
             \return compiled, new pattern
             */
            //__________________________________________________________________
            template <typename STRING> static inline
            Pattern * Compile(const STRING &data, const Dictionary * const dict)
            {
                const Identifier content(data);
                return Compile_(content,dict);
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            static Pattern * Compile_(const Identifier &,const Dictionary * const);
#endif
            
        };
    }

}
#endif // !Y_Jive_RegExp_Included

