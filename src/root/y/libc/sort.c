#include "y/libc/sort.h"
#include <assert.h>
#include <string.h>

void Yttrium_Sort(void * const   a,
                  const size_t   n,
                  const size_t   width,
                  YttriumCompare compare,
                  void * const   rra)
{

    assert(!(NULL==a&&n>0));
    assert(NULL!=compare);
    assert(NULL!=rra);


    if(n<2)
        return;
    else
    {
        size_t l =(n >> 1)+1;
        size_t ir=n;
        char * const ra1 = (char*)a; // first item
        char * const ra = ra1-width; // shifter array
        for(;;)
        {
            if(l>1)
            {
                memcpy(rra,&ra[--l*width],width);
            }
            else
            {
                char * const ra_ir = &ra[ir*width];
                memcpy(rra,ra_ir,width); // rra=ra[ir];
                memcpy(ra_ir,ra1,width); // ra[ir]=ra[1];
                if(--ir == 1)
                {
                    //ra[1]=rra;
                    memcpy(ra1,rra,width);
                    break;
                }
            }
            size_t i = l;
            size_t j = l+l;
            while (j <= ir)
            {
                char * ra_j = &ra[j*width];
                //if (j < ir && ra[j] < ra[j+1]) ++j;
                if( j<ir && compare(ra_j,ra_j+width)<0 ){ ++j; ra_j += width; }

                if( compare(rra,ra_j) < 0 )
                {
                    memcpy(&ra[i*width],ra_j,width);
                    //ra[i]=ra[j];
                    i=j;
                    j <<= 1;
                }
                else
                    break;
                //ra[i]=rra;
                memcpy(&ra[i*width],rra,width);
            }
        }

    }

}
