#include "y/jive/lexical/plugin/string.hpp"
#include "y/string/format.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"
#include "y/format/hexadecimal.hpp"

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

            void String_:: initialize(const char ini,
                                      const char end,
                                      const char * const esc)
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

                // escape backslash
                doEscMark('\\');

                // escape ini/end
                {              doEscMark(ini); }
                { if(ini!=end) doEscMark(end); }

                // escape extra
                {
                    const size_t n = StringLength(esc);
                    for(size_t i=0;i<n;++i) doEscMark(esc[i]);
                }

                // escape control character
                drop("escCntl","[\\\\][nrtvfab]",this, & String_::onEscCntl);

                // escape hexa
                drop("escHexa","[\\\\]x[:xdigit:][:xdigit:]",this, & String_:: onEscHexa );

                // escape exception
                drop("escExcp","[\\\\][:any1:]",this, & String_:: onEscExcp );
            }

            void String_:: onEscExcp(Token &token)
            {
                //std::cerr << "escExcp @'" << token << "'" << std::endl;
                assert(2==token.size);
                const char bad = (char) **token.tail;
                throw Specific::Exception(name->c_str(),"invalid escape sequence starting with '\\%s'", ASCII::Printable::Text(bad) );
            }

            void String_:: onEscCntl(Token &token)  
            {
                assert(2==token.size);
                const char c = (char) **token.tail;
                switch(c)
                {
                    case 'n': **token.head = '\n'; break;
                    case 'r': **token.head = '\r'; break;
                    case 't': **token.head = '\t'; break;
                    case 'v': **token.head = '\v'; break;
                    case 'f': **token.head = '\f'; break;
                    case 'a': **token.head = '\a'; break;
                    case 'b': **token.head = '\b'; break;
                    default:
                        throw Specific::Exception(name->c_str(),"corrupted control char '%s'", ASCII::Printable::Text(c) );
                }
                data.pushTail(token.popHead());
            }

            void String_:: onEscHexa(Token &token) noexcept
            {
                assert(4==token.size);
                Char * const ch = data.pushTail( token.popHead() );
                delete token.popHead();
                assert(2==token.size);
                const int     up = Hexadecimal::ToDec( (char) **token.head); assert(up>=0); assert(up<16);
                const int     lo = Hexadecimal::ToDec( (char) **token.tail); assert(lo>=0); assert(lo<16);
                const uint8_t b  = (uint8_t)(up*16+lo);
                **ch = b;
            }


            void String_:: doChar(const char c)
            {
                drop(c,c,this, & String_::onChar);
            }


            void String_:: doEscMark(const char c)
            {
                const String rx = Formatted::Get("[\\\\]\\x%02x", (unsigned)c);
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


