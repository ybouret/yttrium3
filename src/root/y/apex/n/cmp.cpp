
#include "y/apex/n/code.hpp"
#include "y/apex/k/cmp.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Natural:: Cmp(const Natural &lhs, const Natural &rhs) noexcept
        {
            const KegType &l = *static_cast<const KegType *>(lhs.code);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return KegCmp::Result(l.word, l.words, r.word, r.words);
        }

        SignType Natural:: Cmp(const Natural &lhs, natural_t rhs) noexcept
        {
            const KegType &        l = *static_cast<const KegType *>(lhs.code);
            size_t                 nr = 0;
            const _Keg::Word * wr = Calculus::SplitWord::Make<_Keg::Word>::From(rhs,nr);
            return KegCmp::Result(l.word, l.words, wr, nr);
        }

        SignType Natural:: Cmp(natural_t lhs, const Natural &rhs) noexcept
        {
            size_t             nl = 0;
            const _Keg::Word * wl = Calculus::SplitWord::Make<_Keg::Word>::From(lhs,nl);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return KegCmp::Result(wl,nl,r.word,r.words);
        }
    }
}

