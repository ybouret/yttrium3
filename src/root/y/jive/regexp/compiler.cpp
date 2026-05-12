#include "y/jive/regexp/compiler.hpp"

namespace Yttrium
{

    namespace Jive
    {

        RXCompiler:: RXCompiler(const char * const       userExpr,
                                const size_t             userSize,
                                const Dictionary * const userDict) noexcept :
        expr(userExpr),
        last(expr+userSize),
        dict(userDict)
        {
            assert(0!=expr);
            assert(0!=last);
            
        }


        RXCompiler:: ~RXCompiler() noexcept
        {
        }

    }


}
