#include "y/libc/strfmt.h"
#include "y/utest/run.hpp"

#include <stdarg.h>
#include <stdio.h>

namespace  {

    void vprint(char buffer[], const size_t buflen, const char * const fmt, void * const args)
    {
        va_list *ap = (va_list *)args;
        vsnprintf(buffer,buflen,fmt,*ap);
    }

    void print(char buffer[], const size_t buflen,const char * const fmt, ...)
    {
        va_list ap;
        va_start(ap,fmt);
        vprint(buffer,buflen, fmt, &ap);
        va_end(ap);
    }

}

Y_UTEST(libc_strfmt)
{
    char msg[16] = { 0 };
    print(msg,sizeof(msg),"Hello %s", test);
    std::cerr << msg << std::endl;
}
Y_UDONE()

