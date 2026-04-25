
#include "y/ascii/convert.hpp"
#include <cassert>
#include "y/type/ints.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        int64_t Convert:: ToI64(const char *       text,
                                 size_t             size,
                                 const char * const varName,
                                 const char * const varPart)
        {
            static const char    fn[] = "To uint64_t: ";
            static const int64_t VMAX = IntegerFor<int64_t>::Maximum;
            static const int64_t VMIN = IntegerFor<int64_t>::Minimum;
            static const int64_t VTOP =   VMAX/10;
            static const int64_t VLOW = -(VMIN/10);

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
            int64_t res = 0;

            while(size-- > 0)
            {
                const char c = *(text++);

                if(isNegative)
                {
                    if(res > VLOW)
                    {
                        Specific::Exception excp(CallSign,"%snegative overflow",fn);
                        throw excp.signedFor(varName,varPart);
                    }
                }
                else
                {
                    if(res>VTOP)
                    {
                        Specific::Exception excp(CallSign,"%spositive overflow",fn);
                        throw excp.signedFor(varName,varPart);
                    }
                }

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

            if(res)
            {
                return isNegative ? -res : res;
            }
            else
            {
                return 0;
            }


        }

    }

}


