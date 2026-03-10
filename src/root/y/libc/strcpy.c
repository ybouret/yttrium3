#include "y/libc/strcpy.h"
#include "y/libc/strlen.h"

#include <assert.h>

char * Yttrium_Strcpy(char * const       buffer,
                      const size_t       buflen,
                      const char * const source)
{
    assert(NULL!=buffer);
    assert(buflen>0);

    {
        const size_t bufmax = buflen - 1;
        const size_t srcsiz = Yttrium_Strlen(source);
        const size_t toCopy = srcsiz < bufmax ? srcsiz : bufmax;
        char *       target = buffer;
        for(size_t i=0;i<toCopy;++i)
        {
            *(target++) = source[i];
        }
        assert(target<buffer+buflen);
        *target = 0;
    }

    return buffer;
}
