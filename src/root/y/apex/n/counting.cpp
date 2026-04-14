#include "y/apex/n/code.hpp"
#include "y/apex/k/mul.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{

    namespace Apex
    {
        Natural Natural:: factorial(const natural_t n)
        {
            if(n<=2)
                return Natural(n);
            else
            {
                assert(n>=3);
                AutoPtr<KegType> fac = new KegType(CopyOf,6); // 3!
                for(natural_t i=4;i<=n;++i)
                {
                    const PreComputed I(i);
                    AutoPtr<KegType>  tmp = KegMul::Compute<_Keg::Word,_Keg::Core>(fac->word, fac->words, I.word, I.words);
                    fac = tmp;
                }
                return Natural(Directly,fac.yield());
            }
        }

    }
}
