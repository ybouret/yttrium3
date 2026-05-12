

#include "y/jive/pattern/logic/or.hpp"
#include "y/stream/output.hpp"
#include "y/pointer/auto.hpp"

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

        OutputStream & Or:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "||");
            fp << ",shape=egg";
            Endl(fp<<']');
            return emitLink(fp);
        }

        Pattern * Pattern:: Among(const char * const text, const size_t tlen)
        {
            assert( !(0==text&&tlen>0) );
            AutoPtr<Logic> p = new Or();
            for(size_t i=0;i<tlen;++i)
                 *p << (uint8_t)text[i];
            return p.yield()->optimized();
        }

        Pattern * Pattern:: Among(const char * const text)
        {
            return Among(text,StringLength(text));
        }


        Pattern * Pattern:: Among(const String &s)
        {
            return Among(s.c_str(),s.size());
        }

        Pattern * Or:: optimized()
        {
            noMultiple();
            optimizePatterns();
            alterBasic();
            if(1==size)
            {
                Pattern * const p = popHead();
                delete this;
                return p;
            }
            else
            {
                return this;
            }
        }

        Pattern * Or:: insensitive()
        {
            return this;
        }
    }


}


