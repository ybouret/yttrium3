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

            static Pattern * Compile(const String &,     const Dictionary * const); //!< \return compiled string with optional dictionary
            static Pattern * Compile(const char * const, const Dictionary * const); //!< \return compiled text with optional dictionary
            static Pattern * Compile(const Identifier &, const Dictionary * const); //!< \return compiled identifier content with optional dictionary
            static Pattern * Compile(const char,         const Dictionary * const); //!< \return single byte, dictionary is never used (compatibility only)

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

