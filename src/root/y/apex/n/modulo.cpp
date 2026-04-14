#include "y/apex/n/code.hpp"
#include "y/apex/k/div.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: Modulo(const Natural &lhs, const Natural & rhs)
        {
            const KegType &l = *static_cast<const KegType *>(lhs.code);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly, KegDiv::Rem<_Keg::Word,_Keg::Core>(l.word,l.words, r.word,r.words) );
        }


        Natural Natural:: Modulo(const Natural &lhs, natural_t rhs)
        {
            const KegType &              l = *static_cast<const KegType *>(lhs.code);
            size_t                       n = 0;
            const _Keg::Word * const w = Calculus::SplitWord::Make<_Keg::Word>::From(rhs,n);
            return Natural(Directly, KegDiv::Rem<_Keg::Word,_Keg::Core>(l.word,l.words,w,n) );
        }


        Natural Natural:: Modulo(natural_t lhs, const Natural & rhs)
        {
            size_t                       n = 0;
            const _Keg::Word * const w = Calculus::SplitWord::Make<_Keg::Word>::From(lhs,n);
            const KegType &              r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly, KegDiv::Rem<_Keg::Word,_Keg::Core>(w,n,r.word,r.words) );
        }

    }

}


