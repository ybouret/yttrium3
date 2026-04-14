#include "y/libc/file.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Libc
    {

        File:: ~File() noexcept
        {
            assert(0!=handle);
            if(closeDown)
            {
                (void) fclose(handle);
                Coerce(handle) = 0;
            }
        }

        File:: File(FILE * const fp, const bool autoClose) noexcept :
        handle(fp),
        closeDown(autoClose)
        {
        }


    }

}

