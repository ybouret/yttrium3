
#include "y/jive/pattern/logic/and.hpp"

namespace Yttrium
{
    namespace Jive
    {

        And:: And() noexcept : Logic(UUID)
        {

        }
        

        And:: ~And() noexcept
        {
        }

        And:: And(const And &other) : Logic(other)
        {
        }

        Pattern * And:: clone() const
        {
            return new And(*this);
        }

        bool And:: univocal() const noexcept
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                if(!p->univocal()) return false;
            }
            return true;
        }

        bool And:: sound() const noexcept
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->sound()) return true;
            }
            return false;
        }

        void And:: glean(Leading &leading) const noexcept
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                p->glean(leading);
                if(p->sound()) return;
            }
        }

        bool And:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            for(const Pattern *p=head;p;p=p->next)
            {
                Token sub;
                if(p->takes(sub,source))
                {
                    token.mergeTail(sub);
                }
                else
                {
                    source.unget(token);
                    return false;
                }
            }
            return true;
        }

    }


}
