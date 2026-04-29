

#include "y/apex/integer.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Apex
    {

        static const uint8_t __Zero__Sign = 0x00;
        static const uint8_t PositiveSign = 0x01;
        static const uint8_t NegativeSign = 0x02;


        size_t Integer:: serialize(OutputStream &fp) const
        {
            switch(s)
            {
                case Positive: { size_t res = fp.cbr(PositiveSign); return res + n.serialize(fp); }
                case Negative: { size_t res = fp.cbr(NegativeSign); return res + n.serialize(fp); }
                case __Zero__:
                    break;
            }
            return fp.cbr(__Zero__Sign);

        }
    }

}
