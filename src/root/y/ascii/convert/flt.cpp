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
                    res *= ten;
                    switch(c)
                    {
                        case '0': continue;
                        case '1': res += 1; continue;
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
                    Specific::Exception excp(Convert::CallSign,"%sinvalid '%c' in integer part",fn,c);
                    throw excp.signedFor(varName,varPart);
                }

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


