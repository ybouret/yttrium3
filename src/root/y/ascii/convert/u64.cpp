#include "y/ascii/convert.hpp"
#include <cassert>

namespace Yttrium
{

    namespace ASCII
    {

        namespace
        {
            static const char fn[] = "To uint64_t: ";

            static inline uint64_t ToHex64(const char *      text,
                                           const size_t      size,
                                           const char *const varName,
                                           const char *const varPart)
            {
                static const uint64_t VMAX = IntegerFor<uint64_t>::Maximum;
                static const uint64_t VTOP = VMAX>>4;
                if(size<=0)
                {
                    Specific::Exception excp(Convert::CallSign,"%sempty hexadecimal text",fn);
                    throw excp.signedFor(varName,varPart);
                }

                uint64_t              res  = 0;
                for(size_t i=size;i>0;--i)
                {
                    if(res>VTOP)
                    {
                        Specific::Exception excp(Convert::CallSign,"%shexadecimal overflow",fn);
                        throw excp.signedFor(varName,varPart);
                    }

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


        }


        bool Convert:: HasHexaPrefix(const char * const text,
                                     const size_t       size) noexcept
        {
            assert(text);
            assert(size>0);
            if(size<2)       return false;
            if('0'!=text[0]) return false;
            const char x = text[1];
            if(x!='x' && x!='X') return false;
            return true;
        }



        uint64_t Convert:: ToU64(const char *      text,
                                 const size_t       size,
                                 const char *const varName,
                                 const char *const varPart)
        {

            if(size<=0) { Specific::Exception excp(CallSign,"%sempty text",fn); throw excp.signedFor(varName,varPart); }

            assert(text);

            if( HasHexaPrefix(text,size ))
                return ToHex64(text+2,size-2,varName,varPart);
            else
            {
                static const uint64_t VMAX = IntegerFor<uint64_t>::Maximum;
                static const uint64_t VTOP = VMAX/10;
                uint64_t              res  = 0;

                for(size_t i=size;i>0;--i)
                {
                    if(res>VTOP)
                    {
                        Specific::Exception excp(CallSign,"%sdecimal overflow",fn);
                        throw excp.signedFor(varName,varPart);
                    }
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
        }

    }

}

