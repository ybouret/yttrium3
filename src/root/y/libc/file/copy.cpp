
#include "y/libc/file/copy.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Libc
    {
        void FileCopy:: To(OutputFile &target, InputFile &source)
        {
            char         buf[BUFSIZ];
            FILE * const src = source.handle;
            FILE * const tgt = target.handle;
            Y_Giant_Lock();
            while(true)
            {
                const size_t nr = fread(buf,1,sizeof(buf),src);
                if( ferror(src) )
                    throw Libc::Exception(errno,"fread()");


                if(nr>0)
                {
                    const size_t nw = fwrite(buf,1,nr,tgt);
                    if(nw<nr)
                        throw Libc::Exception(errno,"fwrite()");

                }

                if(nr<BUFSIZ)
                    break;
            }
        }

    }

}
