

#include "y/jive/pattern/logic/or.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Or:: Or() noexcept : Logic(UUID)
        {

        }


        Or:: ~Or() noexcept
        {
        }

        Or:: Or(const Or &other) : Logic(other)
        {
        }

        Pattern * Or:: clone() const
        {
            return new Or(*this);
        }


        bool Or:: sound() const noexcept
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->frail()) return false;
            }
            return true;
        }

        bool Or:: univocal() const noexcept
        {
            switch(size)
            {
                case 0: return true;
                case 1: return head->univocal();
                default:
                    break;
            }
            return false;
        }



        void Or:: glean(Leading &leading) const noexcept
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                p->glean(leading);
            }
        }
        
        bool Or:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            bool res = false;
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->takes(token,source))
                {
                    if(token.size>0)
                        return true;
                    res = true; // continue and left chance for non-emtpy
                }
            }
            return res;
        }

    }


}
