
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

            void Framework:: grow(XNode * const xnode) noexcept
            {
                XNode::Grow(xtree,xnode);
            }

            void Framework:: join(Framework &sub) noexcept
            {
                XNode::Join(xtree,sub.xtree);
            }


            XNode * Framework:: operator->() noexcept
            {
                assert( xtree.isValid() );
                return & *xtree;
            }

            Framework:: Framework(const Replicate_ &, const Framework &parent) noexcept :
            xtree(0),
            lexer(parent.lexer),
            source(parent.source),
            depth(parent.depth)
            {

            }

            void Framework:: dump() noexcept
            {
                assert(xtree.isValid());
                xtree->returnTo(lexer);
                xtree.free();
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
