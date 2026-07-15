
#include "y/libc/file/copy.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {
        void FileCopy:: To(OutputFile &target, InputFile &source)
        {
            char buff[BUFSIZ];
            FILE * const src = source.handle;
            while(true)
            {
                size_t nr = fread(buff,1,BUFSIZ,src);
                if(nr>0)
                {

                }
                if(nr<BUFSIZ)
                    break;
            }
        }

    }

}
