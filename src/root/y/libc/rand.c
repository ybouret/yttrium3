
#include "y/libc/rand.h"
#include <assert.h>
#include <stdlib.h>

#define IA 16807
#define IM 2147483647
#define AMf (1.0f/IM)
#define AMd (1.0/IM)
#define AMl (1.0L/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

static
void Yttrium_RandProlog(long * const seed)
{
    long k; assert(NULL!=seed);

    *seed ^= MASK; k=(*seed)/IQ;
    *seed=IA*(*seed-k*IQ)-IR*k;
    if (*seed < 0) *seed += IM;
}

static
void Yttrium_RandEpilog(long * const seed)
{
    assert(NULL!=seed);
    *seed ^= MASK;
}

float Yttrium_Randf(long * const seed)
{
    float ans;
    assert(NULL!=seed);
    Yttrium_RandProlog(seed);
    ans=AMf*(*seed);
    Yttrium_RandEpilog(seed);
    return ans;
}


double Yttrium_Rand(long * const seed)
{
    double ans;
    assert(NULL!=seed);
    Yttrium_RandProlog(seed);
    ans=AMd*(*seed);
    Yttrium_RandEpilog(seed);
    return ans;
}

long double Yttrium_Randl(long * const seed)
{
    long double ans;
    assert(NULL!=seed);
    Yttrium_RandProlog(seed);
    ans=AMl*(*seed);
    Yttrium_RandEpilog(seed);
    return ans;
}
