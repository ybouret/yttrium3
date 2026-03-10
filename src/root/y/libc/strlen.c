
#include "y/libc/strlen.h"
#include <string.h>

size_t Yttrium_Strlen(const char * const text)
{
    return NULL != text ? strlen(text) : 0;
}
