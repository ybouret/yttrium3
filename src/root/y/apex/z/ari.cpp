
#include "y/apex/integer.hpp"
#include "y/system/exception.hpp"


namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: abs() const
        {
            return n;
        }

        Integer Integer:: sqrt() const
        {
            switch(s)
            {
                case Negative: throw Libc::Exception(EDOM,"negatice %s sqrt", CallSign);
                case __Zero__: return Integer();
                case Positive:
                    break;
            }
            return n.sqrt();
        }

        Integer Integer:: mod2() const
        {
            return n.mod2();
        }

    }

}
