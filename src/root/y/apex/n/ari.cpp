
#include "y/apex/n/code.hpp"
#include "y/calculus/isqrt.hpp"
#include "y/apex/k/cmp.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Natural Natural:: abs() const
        {
            return *this;
        }

        Natural Natural:: sqrt() const
        {
            static const PreComputed last(Calculus::IntegerSquareRoot::TableLast);
            const KegType &          self = *static_cast<KegType *>(code);

            switch( KegCmp::Result(self.word,self.words,last.word,last.words))
            {
                case __Zero__:
                case Negative:
                    assert( self.getNatural() <= last.value );
                    return Calculus::IntegerSquareRoot::Table[ self.getNatural() ];
                case Positive:
                    break;
            }

            const Natural &s  = *this;
            Natural        x0 = s;
            x0.shr();
            //while(true) {
            //Natural x1 = (x0+s/x0)>>1;
            //if(x1>=x0) break;
            //x0 = x1;
            //}
            return x0;

        }

    }

}


