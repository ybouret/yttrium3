#include "y/jive/lexical/plugin/string.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            void String_:: initialize(const char ini, const char end)
            {
                backOn(end,NoEndOfLine);
                drop("core", "[:core:]",this, & String_::onCore);
                
                {              doEscMark(ini); }
                { if(ini!=end) doEscMark(end); }

            }

            void String_:: doEscMark(const char c)
            {
                const String rx = Formatted::Get("\\x%02x", (unsigned)c);
                drop("mark",rx,this, &String_::onEscMark);
            }

            void String_:: onEscMark(Token &token) noexcept
            {
                assert(2==token.size);
                data.pushTail(token.popTail());
            }

            void String_:: onCore(Token &token) noexcept
            {
                assert(1==token.size);
                data.mergeTail(token);
            }

            void String_:: enter(Token &token) noexcept
            {
                assert(token.head);
                spot = *token.head;
                data.release();
            }

            void String_:: leave(Token &)
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


