
#include "y/jive/pattern/logic/none.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        None:: None() noexcept : Logic(UUID)
        {

        }


        None:: ~None() noexcept
        {
        }

        None:: None(const None &other) : Logic(other)
        {
        }

        Pattern * None:: clone() const
        {
            return new None(*this);
        }


        bool None:: sound() const noexcept
        {
            return true;
        }

        bool None:: univocal() const noexcept
        {
            return false;
        }



        void None:: glean(Leading &leading) const noexcept
        {
            Leading res;
            res.all();
            for(const Pattern *p=head;p;p=p->next)
            {
                Leading sub;
                p->glean(sub);
                res -= sub;
            }
            leading << res;
        }

        bool None:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->takes(token,source))
                {
                    source.unget(token);
                    return false;
                }
            }

            Char * const ch = source.get();
            if(!ch) return false;
            token << ch;
            return true;
        }

        OutputStream & None:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "!!");
            fp << ",shape=doubleoctagon";
            Endl(fp<<']');
            return emitLink(fp);
        }

        Pattern * None:: optimized()
        {
            noMultiple();
            optimizePatterns();
            alterBasic();
            return this;
        }

    }


}
