#include "y/ascii/base64/naming.hpp"
#include "y/ascii/base64/encoding.hpp"
#include <cstring>

namespace Yttrium
{
    namespace ASCII
    {
        namespace Base64
        {
            void MakeName:: Encode(char * const name, const size_t nchr, const void *const data, const size_t size) noexcept
            {
                Encoding::Encode( static_cast<char *>(memset(name,0,nchr)), static_cast<const uint8_t *>(data), size);
            }
        }
    }
}
