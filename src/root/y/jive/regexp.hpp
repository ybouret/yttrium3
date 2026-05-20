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
            static Pattern * Compile(const String &,      const Dictionary * const);
            static Pattern * Compile(const char * const,  const Dictionary * const);
            static Pattern * Compile(const Identifier &,  const Dictionary * const);
            static Pattern * Compile(const char,          const Dictionary * const);

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            static Pattern * Compile_(const char * const buffer,
                                      const size_t       length,
                                      const Dictionary * const);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            
        };
    }

}
#endif // !Y_Jive_RegExp_Included

