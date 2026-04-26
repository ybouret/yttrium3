#include "y/ascii/convert.hpp"
#include "y/calculus/ipower.hpp"
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
                     size_t             size)
            {
                static const T ten(10);
                static const T tenth(0.1f);

                assert(text);
                if(size<=0)
                    throw Specific::Exception(Convert::CallSign,"%sempty text",fn);

                bool isNegative = false;
                if('-' == text[0])
                {
                    isNegative = true;
                    ++text;
                    --size;
                    if(size<=0)
                        throw Specific::Exception(Convert::CallSign,"%sempty negative text",fn);
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
                    throw Specific::Exception(Convert::CallSign,"%sinvalid '%c' in integer part",fn,c);
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
                        throw Specific::Exception(Convert::CallSign,"%sinvalid '%c' in fractional part",fn,c);
                    }
                }
                goto RETURN;

            EXPONENT_PART:
                {
                    if(size<=0) {
                        throw Specific::Exception(Convert::CallSign,"%sempty exponent",fn);
                    }
                    bool negativeExponent = false;

                    if('-' == text[0])
                    {
                        ++text;
                        --size;
                        negativeExponent = true;
                        if(size<=0) {
                            throw Specific::Exception(Convert::CallSign,"%sempty negative exponent",fn);
                        }
                    }

                    if('+' == text[0])
                    {
                        ++text;
                        --size;
                        if(size<=0) {
                            throw Specific::Exception(Convert::CallSign,"%sempty positive exponent",fn);
                        }
                    }




                    unsigned xp = 0;
                    while(size-- > 0)
                    {
                        xp *= 10;
                        const char c = *(text++);
                        switch(c)
                        {
                            case '0': continue;
                            case '1': ++xp;    continue;
                            case '2': xp += 2; continue;
                            case '3': xp += 3; continue;
                            case '4': xp += 4; continue;
                            case '5': xp += 5; continue;
                            case '6': xp += 6; continue;
                            case '7': xp += 7; continue;
                            case '8': xp += 8; continue;
                            case '9': xp += 9; continue;
                            default: break;
                        }
                        throw Specific::Exception(Convert::CallSign,"%sinvalid '%c' in exponent",fn,c);
                    }
                    if(xp>0)
                        res *= ipower<T>( negativeExponent ? tenth : ten, xp);
                }


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
                                    const size_t       size)
        {

            return FPConv<float>(text,size);
        }


        template <>
        double Convert:: ToFP<double>(const char * const text,
                                      const size_t       size)
        {
            return FPConv<double>(text,size);
        }

        template <>
        long double Convert:: ToFP<long double>(const char * const text,
                                                const size_t       size)
        {
            return FPConv<double>(text,size);
        }

    }

}


