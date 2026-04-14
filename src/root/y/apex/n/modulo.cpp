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
            return Natural(Directly,KegDiv::Rem<_Keg::Word,_Keg::Core>(l.word,l.words,r.word,r.words));
        }


        Natural Natural:: Modulo(const Natural &lhs, natural_t rhs)
        {
            const KegType &              l = *static_cast<const KegType *>(lhs.code);
            const PreComputed            r(rhs);
            return Natural(Directly,KegDiv::Rem<_Keg::Word,_Keg::Core>(l.word,l.words,r.word,r.words));
        }


        Natural Natural:: Modulo(natural_t lhs, const Natural & rhs)
        {
            const PreComputed l(lhs);
            const KegType &   r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,KegDiv::Rem<_Keg::Word,_Keg::Core>(l.word,l.words,r.word,r.words));
        }

    }

}


