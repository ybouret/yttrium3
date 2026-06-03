
#include "y/jive/syntax/grammar/framework.hpp"
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/lexer.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            Framework:: Framework( Lexer &lxr, Source &src ) noexcept :
            xtree(0),
            lexer(lxr),
            source(src),
            depth(1)
            {

            }

            Framework:: ~Framework() noexcept
            {
            }


            Lexeme * Framework:: get()
            {
                return lexer.pull(source);
            }

            void Framework:: put(Lexeme * const lexeme) noexcept
            {
                assert(lexeme);
                lexer.push(lexeme);
            }
        }

        namespace Syntax
        {
            Nesting:: Nesting(Framework &host) noexcept :
            framework(host)
            {
                ++Coerce(framework.depth);
            }

            Nesting:: ~Nesting() noexcept
            {
                --Coerce(framework.depth);
            }
        }

    }

}
