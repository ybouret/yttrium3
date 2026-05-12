
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{

    namespace Jive
    {
        Pattern * RXCompiler:: subExpr()
        {
            if(curr>=last) throw Specific::Exception(CallSign, "early end of sub-expression in '%s'",expr);
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
                        p->pushTail( subExpr() );
                    } break;

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
                        alt->pushHead(lhs.yield());
                        alt->pushTail(rhs.yield());
                        p->pushHead( alt.yield() );
                    }  goto RETURN;

                        //------------------------------------------------------
                        //
                        // joker
                        //
                        //------------------------------------------------------
                    case '?': p->pushTail( Optional::  Make( extract(*p,'?') )   ); break;
                    case '+': p->pushTail( Repeating:: Make( extract(*p,'+'),1 ) ); break;
                    case '*': p->pushTail( Repeating:: Make( extract(*p,'*'),0 ) ); break;
                        
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
            if(p->size<=0) throw Specific::Exception(CallSign,"empty sub-expression in '%s'",expr);
            return p.yield();
        }

    }

}

