
#include "y/ascii/convert.hpp"
#include <cassert>

namespace Yttrium
{

    namespace ASCII
    {

        apz Convert:: ToAPZ(const char *       text,
                            size_t             size,
                            const char * const varName,
                            const char * const varPart)
        {
            static const char    fn[] = "To apz: ";


            assert(text);
            if(size<=0)
            {
                Specific::Exception excp(Convert::CallSign,"%sempty text",fn);
                throw excp.signedFor(varName,varPart);
            }

            bool isNegative = false;
            if('-' == text[0])
            {
                isNegative = true;
                ++text;
                --size;
                if(size<=0)
                {
                    Specific::Exception excp(CallSign,"%sempty text for negative",fn);
                    throw excp.signedFor(varName,varPart);
                }
            }

            assert(size>0);
            apz res = 0;

            while(size-- > 0)
            {
                const char c = *(text++);
                res *= 10;
                switch(c)
                {
                    case '0':           continue;
                    case '1': ++res;    continue;
                    case '2': res += 2; continue;
                    case '3': res += 3; continue;
                    case '4': res += 4; continue;
                    case '5': res += 5; continue;
                    case '6': res += 6; continue;
                    case '7': res += 7; continue;
                    case '8': res += 8; continue;
                    case '9': res += 9; continue;
                    default:
                        break;
                }
                Specific::Exception excp(CallSign,"%sinvalid decimal '%c'",fn,c);
                throw excp.signedFor(varName,varPart);
            }

            if(isNegative) Sign::MakeOpposite( Coerce(res.s) );

            return res;

        }

    }

}


