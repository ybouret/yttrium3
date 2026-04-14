
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
            return KegCmp::Result(l.word,l.words,r.word,r.words);
        }

        SignType Natural:: Cmp(const Natural &lhs, natural_t rhs) noexcept
        {
            const KegType &   l = *static_cast<const KegType *>(lhs.code);
            const PreComputed r(rhs);
            return KegCmp::Result(l.word,l.words,r.word,r.words);
        }

        SignType Natural:: Cmp(natural_t lhs, const Natural &rhs) noexcept
        {
            const PreComputed  l(lhs);
            const KegType &    r = *static_cast<const KegType *>(rhs.code);
            return KegCmp::Result(l.word,l.words,r.word,r.words);
        }
    }
}

