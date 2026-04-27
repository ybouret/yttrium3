#include "y/libc/str/fmt.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

int Yttrium_Strfmt(char * const       buffer,
                   const size_t       buflen,
                   const char * const fmt,
                   va_list * const    app)
{
    //assert(NULL!=buffer);
    //assert(buflen>0);
    assert(NULL!=fmt);
    assert(NULL!=app);
    
    memset(buffer,0,buflen);
    {
        const int res = vsnprintf(buffer,buflen,fmt,*app);
        if(res<0) memset(buffer,0,buflen);
        return res;
    }
}
