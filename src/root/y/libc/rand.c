
#include "y/libc/rand.h"



#define IA 16807
#define IM 2147483647
#define AM (1.0f/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

float Yttrium_Rand(long * const seed)
{
    long k;
    float ans;
    
    *seed ^= MASK; k=(*seed)/IQ;
    *seed=IA*(*seed-k*IQ)-IR*k;
    if (*seed < 0) *seed += IM;
    ans=AM*(*seed);
    *seed ^= MASK;
    return ans;
}
