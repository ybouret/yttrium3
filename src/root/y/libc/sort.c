#include "y/libc/sort.h"
#include <assert.h>
#include <string.h>


static
void Yttrium_Sort_(void * const   a,
                   const size_t   n,
                   const size_t   wa,
                   YttriumCompare compare,
                   void * const   args,
                   void * const   rra)
{
    size_t l  = (n>>1)+1;
    size_t ir = n;
    char * const ra1 = (char*)a; // first   item
    char * const ra = ra1-wa; // shifted array

    for(;;)
    {
        if(l>1)
        {
            memcpy(rra,&ra[--l*wa],wa);
        }
        else
        {
            char * const ra_ir = &ra[ir*wa];
            memcpy(rra,ra_ir,wa); // rra=ra[ir];
            memcpy(ra_ir,ra1,wa); // ra[ir]=ra[1];
            if(--ir == 1)
            {
                //ra[1]=rra;
                memcpy(ra1,rra,wa);
                break;
            }
        }

        size_t i = l;
        size_t j = l+l;
        while (j<=ir)
        {
            char * ra_j = &ra[j*wa];
            if( (j<ir) && ( compare(ra_j,ra_j+wa,args)<0) )
            {
                ++j;
                ra_j += wa;
            }
            if( compare(rra,ra_j,args) < 0 )
            {
                memcpy(&ra[i*wa],ra_j,wa); //ra[i]=ra[j];
                i=j;
                j <<= 1;
            }
            else
                break;
        }
        memcpy(&ra[i*wa],rra,wa);//ra[i]=rra;
    }

}

void Yttrium_Sort(void * const   a,
                  const size_t   n,
                  const size_t   width,
                  YttriumCompare compare,
                  void * const   args,
                  void * const   rra)
{

    assert(!(NULL==a&&n>0));
    assert(NULL!=compare);
    assert(NULL!=rra);

    switch(n)
    {
        case 0:
        case 1:
            return;
        default:
            assert(n>=2);
            Yttrium_Sort_(a,n,width,compare,args,rra);
    }

}



static
void Yttrium_CoSort_(void * const   a,
                     const size_t   n,
                     const size_t   wa,
                     YttriumCompare compare,
                     void * const   args,
                     void * const   rra,
                     void * const   b,
                     const size_t   wb,
                     void * const   rrb)
{
    size_t l  = (n>>1)+1;
    size_t ir = n;
    char * const ra1 = (char*)a; // first   item
    char * const ra = ra1-wa;    // shifted array
    char * const rb1 = (char*)b;
    char * const rb  = rb1-wb;
    for(;;)
    {
        if(l>1)
        {
            --l;
            memcpy(rra,&ra[l*wa],wa);
            memcpy(rrb,&rb[l*wb],wb);
        }
        else
        {
            char * const ra_ir = &ra[ir*wa];
            char * const rb_ir = &rb[ir*wb];
            memcpy(rra,ra_ir,wa); // rra=ra[ir];
            memcpy(ra_ir,ra1,wa); // ra[ir]=ra[1];
            memcpy(rrb,rb_ir,wb); // rra=ra[ir];
            memcpy(rb_ir,rb1,wb); // ra[ir]=ra[1];
            if(--ir == 1)
            {
                //ra[1]=rra;
                memcpy(ra1,rra,wa);
                memcpy(rb1,rrb,wb);
                break;
            }
        }

        size_t i = l;
        size_t j = l+l;
        while (j<=ir)
        {
            char * ra_j = &ra[j*wa];
            char * rb_j = &rb[j*wb];
            if( (j<ir) && ( compare(ra_j,ra_j+wa,args)<0) )
            {
                ++j;
                ra_j += wa;
                rb_j += wb;
            }
            if( compare(rra,ra_j,args) < 0 )
            {
                memcpy(&ra[i*wa],ra_j,wa); //ra[i]=ra[j];
                memcpy(&rb[i*wb],rb_j,wb);
                i=j;
                j <<= 1;
            }
            else
                break;
        }
        memcpy(&ra[i*wa],rra,wa);//ra[i]=rra;
        memcpy(&rb[i*wb],rrb,wb);
    }

}


void Yttrium_CoSort(void * const   a,
                     const size_t   n,
                     const size_t   wa,
                     YttriumCompare compare,
                     void * const   args,
                     void * const   rra,
                     void * const   b,
                     const size_t   wb,
                     void * const   rrb)
{
    assert(!(NULL==a&&n>0));
    assert(!(NULL==b&&n>0));
    assert(NULL!=compare);
    assert(NULL!=rra);
    assert(NULL!=rrb);

    switch(n)
    {
        case 0:
        case 1:
            return;
        default:
            assert(n>=2);
            Yttrium_CoSort_(a,n,wa,compare,args,rra,b,wb,rrb);
    }
}

