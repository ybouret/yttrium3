//! \file

#ifndef Y_Jive_RegExp_Compiler_Included
#define Y_Jive_RegExp_Compiler_Included 1

#include "y/jive/pattern/dictionary.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Logic;
        
        //______________________________________________________________________
        //
        //
        //
        //! Regular Expression Compiler
        //
        //
        //______________________________________________________________________
        class RXCompiler
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            static const char         LPAREN = '(';    //!< alias
            static const char         RPAREN = ')';    //!< alias
            static const char         ALT    = '|';    //!< alias
            static const char         LBRACK = '[';    //!< alias
            static const char         RBRACK = ']';    //!< alias
            static const char         LBRACE = '{';    //!< alias
            static const char         RBRACE = '}';    //!< alias
            static const char         EscCommSource[]; //!< "nrtvfab"
            static const char         EscCommTarget[]; //!< matching EscCommSource
            static const char         EscExpr[];       //!< allowed escaped char in subExpr
            static const char         EscGroup[];      //!< allowed escaped char in subGroup
            static const char * const CallSign;        //!< "Regular Expresssion"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param userExpr expression
             \param userSize number of chars
             \param userDict optional dictionary
             */
            explicit RXCompiler(const char * const       userExpr,
                                const size_t             userSize,
                                const Dictionary * const userDict) noexcept;

            //! cleanup
            ~RXCompiler() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            //! compile for setup \return compiled pattern
            Pattern * operator()(void);


        private:
            Y_Disable_Copy_And_Assign(RXCompiler); //!< dicarded

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const char *             curr; //!< current char
            const char * const       last; //!< first invalid char
            size_t                   deep; //!< nesting depth
            const char * const       expr; //!< original expression
            const Dictionary * const dict; //!< optional dictionary
            unsigned                 ixpr; //!< sub-expression index
            unsigned                 igrp; //!< sub-group index

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Pattern * subExpr();
            Pattern * extract(Patterns &, const char before);
            Pattern * escExpr();
            Pattern * escHexa();

            Pattern * subGroup();
            Pattern * subPosix();
            Pattern * escGroup();
            uint8_t   getUpper();

            void      braces(Logic &);

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            
        };
    }

}

#endif // !Y_Jive_RegExp_Compiler_Included
