#include "y/ascii/convert.hpp"
#include <cassert>

namespace Yttrium
{

    namespace ASCII
    {

        namespace
        {

            static const char fn[] = "To floating point: ";

            template <typename T> static inline
            T FPConv(const char *       text,
                     size_t             size,
                     const char * const varName,
                     const char * const varPart)
            {
                static const T ten(10);
                static const T tenth(0.1);

                assert(text);
                if(size<=0) {
                    Specific::Exception excp(Convert::CallSign,"%sempty text",fn);
                    throw excp.signedFor(varName,varPart);
                }

                bool isNegative = false;
                if('-' == text[0])
                {
                    isNegative = true;
                    ++text;
                    --size;
                    if(size<=0) {
                        Specific::Exception excp(Convert::CallSign,"%sempty negative text",fn);
                        throw excp.signedFor(varName,varPart);
                    }
                }

                T res = 0;

                // parsing integer part
                while(size-- > 0)
                {
                    const char c = *(text++);
                    switch(c)
                    {
                        case '0': res *= ten; continue;
                        case '1': res *= ten; res += 1; continue;
                        case '2': res *= ten; res += 2; continue;
                        case '3': res *= ten; res += 3; continue;
                        case '4': res *= ten; res += 4; continue;
                        case '5': res *= ten; res += 5; continue;
                        case '6': res *= ten; res += 6; continue;
                        case '7': res *= ten; res += 7; continue;
                        case '8': res *= ten; res += 8; continue;
                        case '9': res *= ten; res += 9; continue;
                        case '.': goto FRACTIONAL_PART;
                        case 'e':
                        case 'E':
                        case 'd':
                        case 'D': goto EXPONENT_PART;
                        default:
                            break;
                    }
                    Specific::Exception excp(Convert::CallSign,"%sinvalid '%c' in integer part",fn,c);
                    throw excp.signedFor(varName,varPart);
                }
                goto RETURN;


            FRACTIONAL_PART:
                {
                    T digit = tenth;
                    while(size-- > 0)
                    {
                        const char c = *(text++);
                        switch(c)
                        {
                            case '0':                 digit *= tenth; continue;
                            case '1': res += 1*digit; digit *= tenth; continue;
                            case '2': res += 2*digit; digit *= tenth; continue;
                            case '3': res += 3*digit; digit *= tenth; continue;
                            case '4': res += 4*digit; digit *= tenth; continue;
                            case '5': res += 5*digit; digit *= tenth; continue;
                            case '6': res += 6*digit; digit *= tenth; continue;
                            case '7': res += 7*digit; digit *= tenth; continue;
                            case '8': res += 8*digit; digit *= tenth; continue;
                            case '9': res += 9*digit; digit *= tenth; continue;
                            case 'e':
                            case 'E':
                            case 'd':
                            case 'D': goto EXPONENT_PART;
                            default:
                                break;
                        }
                        Specific::Exception excp(Convert::CallSign,"%sinvalid '%c' in fractional part",fn,c);
                        throw excp.signedFor(varName,varPart);
                    }
                }
                goto RETURN;

            EXPONENT_PART:
                ;


            RETURN:
                if( res < 0 || res > 0 )
                {
                    return isNegative ? -res : res;
                }
                else
                    return 0;
            }


        }

        template <>
        float Convert:: ToFP<float>(const char * const text,
                                    const size_t       size,
                                    const char * const varName,
                                    const char * const varPart)
        {

            return FPConv<float>(text,size,varName,varPart);
        }


        template <>
        double Convert:: ToFP<double>(const char * const text,
                                      const size_t       size,
                                      const char * const varName,
                                      const char * const varPart)
        {
            return FPConv<double>(text,size,varName,varPart);
        }

        template <>
        long double Convert:: ToFP<long double>(const char * const text,
                                                const size_t       size,
                                                const char * const varName,
                                                const char * const varPart)
        {
            return FPConv<double>(text,size,varName,varPart);
        }

    }

}


