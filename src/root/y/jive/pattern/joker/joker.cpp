#include "y/jive/pattern/joker/joker.hpp"


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

    }
}

