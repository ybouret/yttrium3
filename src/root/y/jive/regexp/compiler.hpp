//! \file

#ifndef Y_Jive_RegExp_Compiler_Included
#define Y_Jive_RegExp_Compiler_Included 1

#include "y/jive/pattern/dictionary.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class RXCompiler
        {
        public:
            static const char LPAREN = '(';
            static const char RPAREN = ')';
            static const char ALT    = '|';
            
            

            static const char * const CallSign; //!< "Regular Expresssion"

            explicit RXCompiler(const char * const       userExpr,
                                const size_t             userSize,
                                const Dictionary * const userDict) noexcept;

            ~RXCompiler() noexcept;

            Pattern * operator()(void);


        private:
            Y_Disable_Copy_And_Assign(RXCompiler);
            const char *             curr;
            const char * const       last;
            size_t                   deep;
            const char * const       expr;
            const Dictionary * const dict;

            Pattern * subExpr();
            Pattern * extract(Patterns &, const char before);

        };
    }

}

#endif // !Y_Jive_RegExp_Compiler_Included
