#include "y/stream/gz/file.hpp"
#include "y/zlib/zlib.h"
#include "y/ability/lockable.hpp"

#include "y/system/exception.hpp"
#include <cassert>
#include <cerrno>

namespace Yttrium
{
    namespace GZ
    {
        static inline
        void *OpenGZFile(const char * const fileName, const char * const mode)
        {
            assert(fileName);
            assert(mode);
            Y_Giant_Lock();
            gzFile fp = gzopen(fileName,mode);
            if(!fp) throw Libc::Exception(errno,"gzOpen(%s,%s)",fileName,mode);
            return fp;
        }

        File:: File(const char * const fileName, const char * const mode) :
        handle( OpenGZFile(fileName,mode) )
        {
        }


        File:: ~File() noexcept
        {
            assert(handle);
            gzFile gz = static_cast<gzFile>(handle);
            Y_Giant_Lock();
            const int err = gzclose(gz);
            if(Z_OK != err)
            {
            }
        }

    }
}
