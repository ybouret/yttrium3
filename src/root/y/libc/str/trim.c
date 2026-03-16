#include "y/libc/str/trim.h"
#include "y/libc/str/len.h"
#include <ctype.h>

char * Yttrium_Strtrim(char * const buffer)
{
    size_t size = Yttrium_Strlen(buffer);
    while(size-- > 0)
    {
        char * const c = buffer+size;
        if(isspace(*c)) {
            *c = 0;
            continue;
        }
        break;
    }
    return buffer;
}

