#include "y/apex/n/code.hpp"
#include "y/apex/k/gcd.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Natural Natural::GCD(const Natural &lhs, const Natural &rhs)
        {
            assert(lhs.code);
            assert(rhs.code);
            const KegType & L = *static_cast<const KegType *>(lhs.code);
            const KegType & R = *static_cast<const KegType *>(rhs.code);
            KegType * const G = KegGCD:: Compute<_Keg::Word,_Keg::Core>(L.word,L.words,R.word,R.words);
            return Natural(Directly,G);
        }

    }

}


namespace Yttrium
{
    namespace Apex
    {

        void Natural::Reduce(Natural &lhs, Natural &rhs)
        {
            static const PreComputed One(1);
            assert(lhs.code);
            assert(rhs.code);
            const KegType &  L = *static_cast<const KegType *>(lhs.code);
            const KegType &  R = *static_cast<const KegType *>(rhs.code);
            AutoPtr<KegType> G = KegGCD:: Compute<_Keg::Word,_Keg::Core>(L.word,L.words,R.word,R.words);
            assert(G->words>0);
            //std::cerr << "G=" << KegDec::ToString<_Keg::Word,_Keg::Core>(*G) << std::endl;
            if( KegCmp::ResultFor(*G,One) == Positive )
            {
                //std::cerr << "simplify!" << std::endl;
                AutoPtr<KegType> newL = KegDiv::Quot<_Keg::Word, _Keg::Core>(L.word,L.words,G->word,G->words);
                AutoPtr<KegType> newR = KegDiv::Quot<_Keg::Word, _Keg::Core>(R.word,R.words,G->word,G->words);
                delete static_cast<const KegType *>(lhs.code);
                delete static_cast<const KegType *>(rhs.code);
                Coerce(lhs.code) = newL.yield();
                Coerce(rhs.code) = newR.yield();
            }

        }

    }

}



