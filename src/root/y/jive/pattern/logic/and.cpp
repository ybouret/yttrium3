
#include "y/jive/pattern/logic/and.hpp"
#include "y/stream/output.hpp"
#include "y/pointer/auto.hpp"

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

        OutputStream & And:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "||");
            fp << ",shape=house";
            Endl(fp<<']');
            return emitLink(fp);
        }

        Pattern * And:: optimized()
        {
            optimizePatterns();
            if(1==size)
            {
                Pattern *p = popHead(); assert(0==size);
                delete this;
                return p;
            }
            else
            {
                return this;
            }
        }


        Pattern * Pattern:: Exact(const char * const text, const size_t tlen)
        {
            assert( !(0==text&&tlen>0) );
            AutoPtr<Logic> p = new And();
            for(size_t i=0;i<tlen;++i)
                *p << text[i];
            return p.yield()->optimized();
        }

        Pattern * Pattern:: Exact(const char * const text)
        {
            return Among(text,StringLength(text));
        }

        Pattern * Pattern:: Exact(const String &s)
        {
            return Among(s.c_str(),s.size());
        }
    }


}
