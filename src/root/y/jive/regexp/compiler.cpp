#include "y/jive/regexp/compiler.hpp"

namespace Yttrium
{

    namespace Jive
    {

        const char * const RXCompiler:: CallSign = "Regular Expresssion";
        
        RXCompiler:: RXCompiler(const char * const       userExpr,
                                const size_t             userSize,
                                const Dictionary * const userDict) noexcept :
        curr(userExpr),
        last(curr+userSize),
        expr(curr),
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
