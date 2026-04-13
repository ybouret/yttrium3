#include "y/apex/n/code.hpp"
#include "y/apex/k/div.hpp"


namespace Yttrium
{
    namespace Apex
    {
        void Natural:: Division(Natural * const quot,
                                Natural * const rem,
                                const Natural & numer,
                                const Natural & denom)
        {
            const KegType & N = *static_cast<const KegType *>(numer.code);
            const KegType & D = *static_cast<const KegType *>(denom.code);

           // AutoPtr<KegType> *q = 0;
           // AutoPtr<KegType> *r = 0;

            KegDiv::Compute<_Keg::WordType,_Keg::CoreType>(0, 0, N.word, N.words, D.word, D.words);


        }
    }
}
