#include "y/jive/pattern/joker/joker.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Joker:: ~Joker() noexcept
        {
        }

        Joker:: Joker(const Joker &jk)   :
        Pattern(jk),
        motif(jk.motif->clone())
        {
        }

        Joker:: Joker(const uint32_t t, const Motif &m) noexcept :
        Pattern(t),
        motif(m)
        {
        }

        void Joker:: glean(Leading &fc) const noexcept
        {
            motif->glean(fc);
        }

        bool Joker:: HaveSameMotif(const Joker &lhs, const Joker &rhs) noexcept
        {
            return AreEqual(*lhs.motif, *rhs.motif);
        }

        OutputStream & Joker:: emitLink(OutputStream &fp) const
        {
            motif->viz(fp);
            return Endl( to( & *motif, fp) );
        }

        void Joker:: optimizeMotif()
        {
            Motif   m( Optimized(motif->clone()) );
            Coerce(motif).xch(m);
        }

        void Joker:: insensitiveMotif()
        {
            Motif   m( Insensitive(motif->clone()) );
            Coerce(motif).xch(m);
        }
    }
}

