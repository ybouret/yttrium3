

#include "y/apex/n/code.hpp"
#include "y/apex/k/sub.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: Sub(const Natural &lhs, const Natural & rhs)
        {
            const KegType &l = *static_cast<const KegType *>(lhs.code);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegSub::Compute<_Keg::WordType,_Keg::Core>(l.word,l.words,
                                                                      r.word,r.words) );
        }


        Natural Natural:: Sub(const Natural &lhs, natural_t rhs)
        {
            const KegType &   l = *static_cast<const KegType *>(lhs.code);
            const PreComputed r(rhs);
            return Natural(Directly,
                           KegSub::Compute<_Keg::WordType,_Keg::Core>(l.word,l.words,
                                                                      r.word,r.words) );
        }


        Natural Natural:: Sub(natural_t lhs, const Natural & rhs)
        {
            const PreComputed l(lhs);
            const KegType &   r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegSub::Compute<_Keg::WordType,_Keg::Core>(l.word,l.words,
                                                                      r.word,r.words) );
        }

        Natural Natural:: predecessor() const
        {
            static const _Keg::WordType one = 1;
            const KegType & l = *static_cast<const KegType *>(code);
            return Natural(Directly,
                           KegSub::Compute<_Keg::WordType,_Keg::Core>(l.word,l.words,
                                                                      &one,1) );
        }

        Natural & Natural:: operator--()
        {
            Natural tmp = predecessor();
            return xch(tmp);
        }

        Natural Natural:: operator--(int)
        {
            const Natural res = *this;
            { Natural tmp = predecessor(); (void) xch(tmp); }
            return res;
        }

    }
    
}


