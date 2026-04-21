

#include "y/apex/n/code.hpp"
#include "y/apex/k/mul.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: Mul(const Natural &lhs, const Natural & rhs)
        {
            const KegType &l = *static_cast<const KegType *>(lhs.code);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegMul::Compute<_Keg::Word,_Keg::Core>(l.word,l.words,
                                                                  r.word,r.words) );
        }


        Natural Natural:: Mul(const Natural &lhs, natural_t rhs)
        {
            const KegType &   l = *static_cast<const KegType *>(lhs.code);
            const PreComputed r(rhs);
            return Natural(Directly,
                           KegMul::Compute<_Keg::Word,_Keg::Core>(l.word,l.words,
                                                                  r.word,r.words) );
        }


        Natural Natural:: Mul(natural_t lhs, const Natural & rhs)
        {
            const PreComputed l(lhs);
            const KegType &   r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegMul::Compute<_Keg::Word,_Keg::Core>(l.word,l.words,
                                                                  r.word,r.words) );
        }

        Natural Natural:: mod2() const
        {
            const KegType & k = *static_cast<const KegType *>(code);
            return Natural(Directly, KegMul::Square<_Keg::Word,_Keg::Core>(k.word,k.words) );
        }



    }

}


