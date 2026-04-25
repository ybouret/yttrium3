
#include "y/ascii/convert.hpp"
#include <cassert>

namespace Yttrium
{

    namespace ASCII
    {

        namespace
        {
            static const char fn[] = "To apn: ";
        }

        apn Convert:: ToHexAPN(const char *text, const size_t size, const char *const varName, const char *const varPart)
        {
            assert(text);
            if(size<=0) {
                Specific::Exception excp(CallSign,"%sempty hexadecimal text",fn);
                throw excp.signedFor(varName,varPart);
            }

            apn res = 0;


            for(size_t i=size;i>0;--i)
            {
                res <<= 4;
                const char c = *(text++);
                switch( c )
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
                    case 'a':
                    case 'A': res += 10; continue;
                    case 'b':
                    case 'B': res += 11; continue;
                    case 'c':
                    case 'C': res += 12; continue;
                    case 'd':
                    case 'D': res += 13; continue;
                    case 'e':
                    case 'E': res += 14; continue;
                    case 'f':
                    case 'F': res += 15; continue;

                    default:
                        break;
                }
                Specific::Exception excp(Convert::CallSign,"%sinvalid hexadecimal '%c'",fn,c);
                throw excp.signedFor(varName,varPart);
            }

            return res;
        }


        apn Convert:: ToDecAPN(const char *       text,
                               const size_t       size,
                               const char * const varName,
                               const char * const varPart)
        {
            assert(text);
            if(size<=0) {
                Specific::Exception excp(CallSign,"%sempty decimal text",fn);
                throw excp.signedFor(varName,varPart);
            }

            apn res = 0;
            for(size_t i=size;i>0;--i)
            {
                res *= 10;

                const char c = *(text++);
                switch( c )
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

            return res;
        }

        apn Convert:: ToAPN(const char * const text,
                            const size_t       size,
                            const char * const varName,
                            const char * const varPart)
        {
            if(size<=0)
            {
                Specific::Exception excp(CallSign,"%sempty text",fn);
                throw excp.signedFor(varName,varPart);
            }

            if(HasHexaPrefix(text,size))
            {
                return ToHexAPN(text+2,size-2,varName,varPart);
            }
            else
            {
                return ToDecAPN(text,size,varName,varPart);
            }
            
        }
    }
}

