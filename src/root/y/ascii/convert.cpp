#include "y/ascii/convert.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        const char * const Convert:: CallSign = "ASCII::Convert";


        template <>
        apz Convert:: ToAP<apz>(const char * const text,
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart)
        {
            return ToAPZ(text,size,varName,varPart);
        }

        template <>
        apn Convert:: ToAP<apn>(const char * const text,
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart)
        {
            return ToAPN(text,size,varName,varPart);
        }
    }

}

