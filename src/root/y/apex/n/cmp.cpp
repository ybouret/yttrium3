
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
    }
}

