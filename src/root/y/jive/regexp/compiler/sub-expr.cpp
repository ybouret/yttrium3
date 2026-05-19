
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/posix.hpp"

namespace Yttrium
{

    namespace Jive
    {
        Pattern * RXCompiler:: subExpr()
        {
            ++ixpr;
            if(curr>=last) throw Specific::Exception(CallSign, "early end of sub-expression #%u in '%s'",ixpr,expr);
            AutoPtr<Logic> p = new And();

            while(curr<last)
            {
                const char c = *(curr++);

                switch(c)
                {

                        //------------------------------------------------------
                        //
                        // grouping
                        //
                        //------------------------------------------------------
                    case LPAREN: {
                        ++deep;
                        *p << subExpr();
                    } continue;

                    case RPAREN: {
                        if(!deep) throw Specific::Exception(CallSign,"extraneous '%c' in '%s'",RPAREN,expr);
                        --deep;
                    } goto RETURN;

                        //------------------------------------------------------
                        //
                        // Alternate
                        //
                        //------------------------------------------------------
                    case ALT: {
                        if(p->size<=0) throw Specific::Exception(CallSign, "no sub-expression before '%c' in '%s'", ALT, expr);
                        AutoPtr<Logic>   alt = new Or(); // prepare new pattern
                        AutoPtr<Logic>   lhs = new And();
                        AutoPtr<Pattern> rhs = subExpr();
                        lhs->swapForList(*p);
                        *alt << lhs.yield();
                        *alt << rhs.yield();
                        *p   << alt.yield();
                    }  goto RETURN;

                        //------------------------------------------------------
                        //
                        // joker
                        //
                        //------------------------------------------------------
                    case '?': *p << Optional::  Make( extract(*p,'?') );     continue;
                    case '+': *p << Repeating:: Make( extract(*p,'+'),1 );   continue;
                    case '*': *p << Repeating:: Make( extract(*p,'*'),0 );   continue;
                    case '&': *p << Pattern::Insensitive( extract(*p,'&') ); continue;

                        //------------------------------------------------------
                        //
                        // escape sequence
                        //
                        //------------------------------------------------------
                    case '\\': *p << escExpr(); continue;

                        //------------------------------------------------------
                        //
                        // specific
                        //
                        //------------------------------------------------------
                    case '.' : *p << posix::dot(); continue;


                        //------------------------------------------------------
                        //
                        // braces
                        //
                        //------------------------------------------------------
                    case LBRACE: braces(*p); continue;

                        //------------------------------------------------------
                        //
                        // subGroup
                        //
                        //------------------------------------------------------
                    case LBRACK: *p << subGroup(); continue;

                        //------------------------------------------------------
                        //
                        // default
                        //
                        //------------------------------------------------------
                    default:
                        *p << (uint8_t)c;
                }
            }

        RETURN:
            if(p->size<=0) throw Specific::Exception(CallSign,"empty sub-expression #%u in '%s'",ixpr,expr);
            return p.yield();
        }

    }

}

