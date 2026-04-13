
#include "y/apex/n/code.hpp"
#include "y/apex/k/add.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: operator+() const
        {
            return *this;
        }

        Natural Natural:: Add(const Natural &lhs, const Natural & rhs)
        {
            const KegType &l = *static_cast<const KegType *>(lhs.code);
            const KegType &r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegAdd::Compute<_Keg::WordType,_Keg::CoreType>(l.word,l.words,
                                                                          r.word,r.words) );
        }


        Natural Natural:: Add(const Natural &lhs, natural_t rhs)
        {
            const KegType &    l = *static_cast<const KegType *>(lhs.code);
            const PreComputed  r(rhs);
            return Natural(Directly,
                           KegAdd::Compute<_Keg::WordType,_Keg::CoreType>(l.word,l.words,
                                                                          r.word,r.words) );
        }


        Natural Natural:: Add(natural_t lhs, const Natural & rhs)
        {
            const PreComputed l(lhs);
            const KegType &   r = *static_cast<const KegType *>(rhs.code);
            return Natural(Directly,
                           KegAdd::Compute<_Keg::WordType,_Keg::CoreType>(l.word,l.words,
                                                                          r.word,r.words) );
        }

        Natural Natural:: successor() const
        {
            static const _Keg::WordType one = 1;
            const KegType & l = *static_cast<const KegType *>(code);
            return Natural(Directly,
                           KegAdd::Compute<_Keg::WordType,_Keg::CoreType>(l.word,l.words,
                                                                          &one,1) );
        }

        Natural & Natural:: operator++()
        {
            Natural tmp = successor();
            return xch(tmp);
        }

        Natural Natural:: operator++(int)
        {
            const Natural res = *this;
            { Natural tmp = successor(); (void) xch(tmp); }
            return res;
        }

    }

}


