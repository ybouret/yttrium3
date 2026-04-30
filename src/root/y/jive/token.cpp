
#include "y/jive/token.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Token:: ~Token() noexcept
        {
        }

        Token:: Token(const Token &t) : CxxList(t) {}

        Token:: Token() noexcept
        {
        }

        Token & Token:: operator<<(Char * const ch) noexcept
        {
            pushTail(ch);
            return *this;
        }


        Token & Token:: operator>>(Char * const ch) noexcept
        {
            pushHead(ch);
            return *this;
        }

        String Token:: toString() const
        {
            String res;
            for(const Char *ch=head;ch;ch=ch->next)
            {
                res += ASCII::Printable::Char[ **ch ];
            }
            return res;
        }

        std::ostream & operator<<(std::ostream &os, const Token &token)
        {
            return os << token.toString();
        }

    }

}
