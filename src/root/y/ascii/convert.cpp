#include "y/ascii/convert.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        const char * const Convert:: CallSign = "ASCII::Convert";


        template <>
        apz Convert:: ToAP<apz>(const char * const text,
                                const size_t       size)
        {
            return ToAPZ(text,size);
        }

        template <>
        apn Convert:: ToAP<apn>(const char * const text,
                                const size_t       size)
        {
            return ToAPN(text,size);
        }
    }

}

