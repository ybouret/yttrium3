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
            explicit RXCompiler(const char * const       userExpr,
                                const size_t             userSize,
                                const Dictionary * const userDict) noexcept;

            ~RXCompiler() noexcept;

        private:
            Y_Disable_Copy_And_Assign(RXCompiler);
            const char * const       expr;
            const char * const       last;
            const Dictionary * const dict;
        };
    }

}

#endif // !Y_Jive_RegExp_Compiler_Included
