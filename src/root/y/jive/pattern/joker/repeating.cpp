

#include "y/jive/pattern/joker/repeating.hpp"
#include "y/exception.hpp"
#include "y/stream/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Repeating:: ~Repeating() noexcept
        {
        }

        Repeating:: Repeating(const Motif &m, const size_t nmin)  :
        Joker(UUID,m),
        atLeast(nmin)
        {
            if(motif->frail())
                throw Specific::Exception(name,"forbidden frail motif '%s'", motif->name);
        }

        Repeating:: Repeating(const Repeating &rep) :
        Joker(rep),
        atLeast(rep.atLeast)
        {
        }

        Pattern * Repeating:: clone() const
        {
            return new Repeating(*this);
        }

        bool Repeating:: univocal() const noexcept
        {
            return false;
        }

        size_t Repeating:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res += fp.vbr(atLeast);
            return res+motif->serialize(fp);
        }

        bool Repeating:: sound() const noexcept
        {
            return atLeast>0;
        }

        bool Repeating:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            size_t count = 0;
            while(true)
            {
                Token sub;
                if(motif->takes(sub,source))
                {
                    ++count;
                    token.mergeTail(sub);
                }
                else
                    break;
            }

            if(count>=atLeast)
                return true;
            else
            {
                source.unget(token);
                return false;
            }
        }

        Repeating * Repeating::Make(Pattern * const p, const size_t nmin)
        {
            const Motif m = p;
            return new Repeating(p,nmin);
        }


        OutputStream & Repeating:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            switch(atLeast)
            {
                case 0: Label(fp,"*"); break;
                case 1: Label(fp,"+"); break;
                default:
                {
                    const String label = Formatted:: Get(">=%s", Decimal(atLeast).c_str());
                    Label(fp,label);
                }
            }
            fp << ",shape=trapezium";
            Endl(fp<<']');
            return emitLink(fp);
        }

    }

}
