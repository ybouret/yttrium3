

#include "y/apex/integer.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Apex
    {

        static const uint8_t Mark__Zero__ = 0x00;
        static const uint8_t MarkPositive = 0x01;
        static const uint8_t MarkNegative = 0x02;


        size_t Integer:: serialize(OutputStream &fp) const
        {
            switch(s)
            {
                case Positive: { size_t res = fp.cbr(MarkPositive); return res + n.serialize(fp); }
                case Negative: { size_t res = fp.cbr(MarkNegative); return res + n.serialize(fp); }
                case __Zero__:
                    break;
            }
            return fp.cbr(Mark__Zero__);

        }

        Integer Integer:: Read(InputStream &fp, const char * const varName)
        {
            const uint8_t mark = fp.cbr<uint8_t>(varName,"sign");
            SignType      mine = __Zero__;
            switch(mark)
            {
                case Mark__Zero__: return Integer();
                case MarkPositive: mine = Positive; break;
                case MarkNegative: mine = Negative; break;
                default:
                {
                    Specific::Exception excp(CallSign,"invalid mark 0x%02x",mark);
                    throw excp.signedFor(varName,"sign");
                }
            }
            const Natural zabs = Natural::Read(fp,varName);
            if(zabs.is0())
            {
                Specific::Exception excp(CallSign,"corrupted absolute value");
                throw excp.signedFor(varName,"natural part");
            }
            return Integer(mine,zabs);
        }


    }


}
