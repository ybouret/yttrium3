#include "y/jive/lexical/plugin/string.hpp"
#include "y/string/format.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            String_:: ~String_() noexcept
            {}

            Leading String_:: GetCore() noexcept
            {
                Leading core;
                core << ' ' << '!';
                core << Within('#','&');
                core << Within('(',';');
                core << '=';
                core << Within('?','[');
                core << Within(']','~');
                return core;
            }

            void String_:: initialize(const char ini, const char end)
            {
                // return on end char
                backOn(end,NoEndOfLine);

                // build core
                {
                    Leading core = GetCore();
                    for(unsigned i=32;i<127;++i)
                        if( core.get( (uint8_t)i ) )
                            doChar( (char)i );
                }

                // escape ini/end
                {              doEscMark(ini); }
                { if(ini!=end) doEscMark(end); }

            }

            void String_:: doChar(const char c)
            {
                drop(c,c,this, & String_::onChar);
            }


            void String_:: doEscMark(const char c)
            {
                const String rx = Formatted::Get("\\x%02x", (unsigned)c);
                drop(c,rx,this, &String_::onEscMark);
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


            void String_:: onChar(Token &token) noexcept
            {
                assert(1==token.size);
                data.mergeTail(token);
            }

        }

    }

}


