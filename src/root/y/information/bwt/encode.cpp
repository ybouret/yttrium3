#include "y/information/bwt/bwt.hpp"
#include "y/libc/sort.h"
#include <cassert>

namespace Yttrium
{
    namespace Information
    {
        namespace
        {
            struct rotlexdat
            {
                const uint8_t *buf;
                size_t         len;
            };

            static int rotlexcmp(const void *lhs, const void *rhs, void *args)
            {
                const struct rotlexdat *rotlex = (const struct rotlexdat *)args;
                assert(lhs);
                assert(rhs);
                assert(args);
                assert(rotlex->buf);
                assert(rotlex->len);

                {
                    size_t li = *(const size_t *)lhs;
                    size_t ri = *(const size_t *)rhs;
                    if(li==ri)
                        return 0;
                    else
                    {
                        const uint8_t *buf = rotlex->buf;
                        const size_t   len = rotlex->len;
                        size_t         ac  = len;
                        while( buf[li] == buf[ri] )
                        {
                            li = (li+1) % len;
                            ri = (ri+1) % len;
                            if( --ac == 0 )
                                return 0;
                        }
                        return (buf[li] < buf[ri]) ? -1 : 1;
                    }
                }

            }

            static void Y_BWT_Build(size_t * const        indices,
                                    const uint8_t * const buf_in,
                                    const size_t          size) noexcept
            {
                struct rotlexdat  rotlex  = { buf_in, size };
                size_t            i = 0;
                for(i=0;i<size;++i) indices[i] = i;
                Yttrium_Sort(indices,size,sizeof(size_t), rotlexcmp, &rotlex, &i);
                //Sorting::Heap::Sort(indices,size,sizeof(size_t), &i, rotlexcmp, &rotlex);
                
            }
        }
        
        size_t BWT:: Encode(void * const output, const void * const input, const size_t size, size_t * const indices) noexcept
        {
            assert(!(0==output&&size>0));
            assert(!(0==input&&size>0));
            assert(!(0==indices&&size>0));

            if(size<=0)
            {
                return 0;
            }
            else
            {
                /* prepare data */
                const uint8_t    *buf_in  = (const uint8_t *)input;
                uint8_t          *buf_out = (uint8_t       *)output;
                size_t            pidx    = 0;
                const size_t      shft    = size-1;
                Y_BWT_Build(indices,buf_in,size);

                {
                    size_t i;
                    /* find primary index */
                    for(i=0;i<size;++i)
                    {
                        const size_t idx = indices[i];
                        buf_out[i] = buf_in[ (idx+shft) % size];
                        if(0==idx)
                        {
                            pidx=i;
                            break;
                        }
                    }

                    for(++i;i<size;++i)
                    {
                        buf_out[i] = buf_in[ (indices[i]+shft) % size];
                    }
                }
                return pidx;
            }
        }


    }

}
