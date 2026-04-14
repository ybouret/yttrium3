
#include "y/libc/file/output.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/string.hpp"

#include <cassert>
#include <cerrno>
#include <cstring>

namespace Yttrium
{
    namespace Libc
    {
        OutputFile:: ~OutputFile() noexcept
        {

        }

        OutputFile:: OutputFile(const StdOut_ &) :
        File(stdout,false)
        {
            if(!stdout) throw Libc::Exception(EIO,"no stdout!");
        }


        OutputFile:: OutputFile(const StdErr_ &) :
        File(stderr,false)
        {
            if(!stderr) throw Libc::Exception(EIO,"no stderr!");
        }


        static inline
        FILE * OpenFileWA(const char * const fileName,
                          bool &             closeDown,
                          const bool         append)
        {
            assert(fileName);

            if( 0 == strcmp(fileName,Y_STDOUT) )
            {
                closeDown = false;
                if(!stdout) throw Libc::Exception(EIO,"no stdout!");
                return stdout;
            }

            if( 0 == strcmp(fileName,Y_STDERR) )
            {
                closeDown = false;
                if(!stderr) throw Libc::Exception(EIO,"no stderr!");
                return stderr;
            }

            Y_Giant_Lock();
            const char * const mode = append ? "ab" : "wb";
            FILE * const fp = fopen(fileName,mode);
            if(!fp) throw Libc::Exception(errno,"fopen(%s)",fileName);
            closeDown = true;
            return fp;

        }

        OutputFile:: OutputFile(const char * const fileName,
                                const bool         append) :
        File(0,true)
        {
            Coerce(handle)  = OpenFileWA(fileName,Coerce(closeDown), append);
            if(closeDown) bufferize();

        }

        OutputFile:: OutputFile(const String & fileName,
                                const bool     append) :
        File(0,true)
        {
            Coerce(handle)  = OpenFileWA(fileName.c_str(),Coerce(closeDown), append);
            if(closeDown) bufferize();
        }


    }

}


