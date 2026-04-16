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

