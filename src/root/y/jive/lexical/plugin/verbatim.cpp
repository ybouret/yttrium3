
#include "y/jive/lexical/plugin/verbatim.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            const char * const Verbatim:: Expression = "\\x5cverb";

            Verbatim:: ~Verbatim() noexcept
            {
            }

            void Verbatim:: initialize()
            {
                backOn(Expression,NoEndOfLine);
                drop("char", "[\\x00-\\xff]",this, & Verbatim::onChar);
            }

            void Verbatim:: onChar(Token &token) noexcept
            {
                assert(1==token.size);
                data.mergeTail(token);
            }

            

            void Verbatim:: enter(Token &ini) noexcept
            {
                // ini should be '\verb'
                assert(ini.size>0);
                spot = *ini.tail;
                data.release();
            }

            void Verbatim:: leave(Token &) noexcept
            {
                Unit * lx = new Unit(spot,name);
                lx->swapForList(data);
                assert(0==data.size);
                spot.set(name);
                stack.push(lx);
            }

        }
    }

}


