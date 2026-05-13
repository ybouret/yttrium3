#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"
#include "y/jive/pattern/posix.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{

    namespace Jive
    {


        uint8_t RXCompiler:: getUpper()
        {
            assert(curr<last);
            assert('-' == curr[-1]);

            const char c = *(curr++);

            switch(c)
            {
                case LBRACK:
                case RBRACK:
                    throw Specific::Exception(CallSign, "forbidden '%s' after '-' in sub-group #%u of '%s'",
                                              ASCII::Printable::Text(c),
                                              igrp,expr);

                case '\\': {
                    AutoPtr<Pattern> p = escGroup(); assert(Byte::UUID==p->uuid);
                    return dynamic_cast<Byte&>(*p).code;
                }

                default:
                    break;
            }

            return (uint8_t)c;
        }

        Pattern * RXCompiler:: subGroup()
        {
            assert(LBRACK == curr[-1]);
            ++igrp;

            if(curr>=last) throw Specific::Exception(CallSign, "early end of sub-group #%u in '%s'",igrp,expr);

            AutoPtr<Logic> g = 0;

            //------------------------------------------------------------------
            //
            // check first char
            //
            //------------------------------------------------------------------
            switch(*curr)
            {
                case ':': ++curr; return subPosix();
                case '^': g = new None();  ++curr; break;
                default:  g = new Or();            break;
            }

            //------------------------------------------------------------------
            //
            // Loop
            //
            //------------------------------------------------------------------
            while(curr<last)
            {
                const char c = *(curr++);

                switch(c)
                {
                        // end or start new group
                    case LBRACK: *g << subGroup(); continue;
                    case RBRACK: goto RETURN;

                        // escape sequence
                    case '\\': *g << escGroup(); continue;

                        // lump
                    case '-':
                        if(g->size<=0)
                            *g << (uint8_t)c;
                        else
                        {
                            // check there is a single byte before '-'
                            if(Byte::UUID != g->tail->uuid)
                                throw Specific::Exception(CallSign,"no char in sub-group #%u before '-' in '%s'",igrp,expr);

                            // check there is some data
                            if(curr>=last)
                                throw Specific::Exception(CallSign,"unfinished sub-group #%u range in '%s'",igrp,expr);

                            // extract parameters
                            const uint8_t lower = dynamic_cast<Byte*>(g->tail)->code; delete g->popTail();
                            const uint8_t upper = getUpper();
                            *g << Within(lower,upper);
                        }
                        continue;

                        // default
                    default: *g << (uint8_t)c;
                }

            }

            throw Specific::Exception(CallSign,"unfinished sub-group #%u in '%s'",igrp,expr);

        RETURN:
            if(g->size<=0) throw Specific::Exception(CallSign,"empty sub-group #%u in '%s'",igrp,expr);
            return g.yield();
        }

    }

}

