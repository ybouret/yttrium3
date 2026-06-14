
#include "y/jive/token.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Token:: ~Token() noexcept
        {
        }

        Token:: Token(const Token &t) : CxxListOf<Char>(t) {}

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

        String Token:: str(const size_t skip, const size_t trim) const
        {
            const size_t drop = skip+trim; assert(drop<=size);
            String res;
            const Char * ch=head;
            for(size_t i=skip;i>0;--i) { assert(ch); ch=ch->next; }
            for(size_t i=size-drop;i>0;--i,ch=ch->next)
            {
                assert(ch);
                res += ASCII::Printable::Char[ **ch ];
            }
            return res;
        }

        std::ostream & operator<<(std::ostream &os, const Token &token)
        {
            return os << token.str();
        }


        bool Token:: AreEqual(const Token &lhs, const Token &rhs) noexcept
        {
            if(lhs.size!=rhs.size) return false;
            for(const Char *l=lhs.head, *r=rhs.head;l;l=l->next,r=r->next)
            {
                assert(l);
                assert(r);
                if(**l != **r) return false;
            }
            return true;
        }

        bool operator==(const Token &lhs, const Token &rhs) noexcept
        {
            return Token::AreEqual(lhs,rhs);
        }

        bool operator!=(const Token &lhs, const Token &rhs) noexcept
        {
            return !Token::AreEqual(lhs,rhs);
        }

    }

}
