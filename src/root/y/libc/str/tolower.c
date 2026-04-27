#include "y/libc/str/tolower.h"
#include <ctype.h>
#include <assert.h>

char * Yttrium_StrToLower(char * const buffer, const size_t buflen)
{
    char * p = buffer; assert(!(buffer==0&&buflen>0));
    for(size_t i=buflen;i>0;--i,++p)
    {
        *p = (char) tolower(*p);
    }
    
    return buffer;

}
