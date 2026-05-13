#include "y/jive/regexp/compiler.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"
#include "y/ascii/printable.hpp"

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
        deep(0),
        expr(curr),
        dict(userDict)
        {
            assert(0!=expr);
            assert(0!=last);
            
        }


        RXCompiler:: ~RXCompiler() noexcept
        {
        }

        Pattern * RXCompiler:: operator()(void)
        {
            AutoPtr<Pattern> res = subExpr();
            if(deep>0)
                throw Specific::Exception(CallSign,"unfinished %s-deep sub-expression in '%s'", Decimal(deep).c_str(),expr);
            //return res.yield();
            return Pattern::Optimized(res.yield());
        }

        Pattern * RXCompiler:: extract(Patterns &list, const char before)
        {
            if(list.size<=0) throw Specific::Exception(CallSign, "no sub-expression before '%s'",ASCII::Printable::Text(before));
            return list.popTail();
        }


    }


}
