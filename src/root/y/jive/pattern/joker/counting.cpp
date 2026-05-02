


#include "y/jive/pattern/joker/counting.hpp"
#include "y/exception.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Counting:: ~Counting() noexcept
        {
        }

        Counting:: Counting(const Motif &m, const size_t nmin, const size_t nmax)  :
        Joker(UUID,m),
        lower(nmin),
        upper(nmax)
        {
            if(lower>upper) CoerceSwap(lower,upper);
            if(motif->frail())
                throw Specific::Exception(name,"forbidden frail motif '%s'", motif->name);
        }

        Counting:: Counting(const Counting &p) :
        Joker(p),
        lower(p.lower),
        upper(p.upper)
        {
        }

        Pattern * Counting:: clone() const
        {
            return new Counting(*this);
        }

        bool Counting:: univocal() const noexcept
        {
            return lower>0 && upper==lower && motif->univocal();
        }

        size_t Counting:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res += fp.vbr(lower);
            res += fp.vbr(upper);
            return res+motif->serialize(fp);
        }

        bool Counting:: sound() const noexcept
        {
            return lower>0;
        }

        bool Counting:: takes(Token &token, Source &source) const
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

            if(count>=lower&&count<=upper)
                return true;
            else
            {
                source.unget(token);
                return false;
            }
        }

        Counting * Counting::Make(Pattern * const p, const size_t nmin, const size_t nmax)
        {
            const Motif m = p;
            return new Counting(p,nmin,nmax);
        }


    }

}
