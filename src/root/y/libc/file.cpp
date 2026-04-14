#include "y/libc/file.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Libc
    {

        void File:: autoClose() noexcept
        {
            if(handle && closeDown)
            {
                (void) fclose(handle);
            }
            Coerce(handle) = 0;

        }

        File:: ~File() noexcept
        {
            autoClose();
        }

        File:: File(FILE * const fp, const bool autoClose) noexcept :
        handle(fp),
        closeDown(autoClose),
        buffer()
        {
        }



    }

}

#include "y/libc/file/buffer.hpp"

namespace Yttrium
{
    namespace Libc
    {
        void File:: bufferize()
        {
            assert(handle);
            assert(buffer.isEmpty());
            assert(closeDown);
            
            try
            {
                buffer = new FileBuffer();
            }
            catch(...)
            {
                autoClose();
                throw;
            }
        }

    }
}
