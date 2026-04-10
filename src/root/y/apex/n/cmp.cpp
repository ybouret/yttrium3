
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

        SignType Natural:: Cmp(const Natural &lhs,   natural_t rhs) noexcept
        {
            const KegType &        lk = *static_cast<const KegType *>(lhs.code);
            size_t                 nr = 0;
            const _Keg::WordType * wr = Calculus::SplitWord::Make<_Keg::WordType>::From(rhs,nr);

        }


    }
}

